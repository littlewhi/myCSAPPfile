#include <stdio.h>
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *connectclose = "Connection: close\r\n";
static const char *proxyconnect = "Proxy-Connection: close\r\n";
// Connection: close
// Proxy-Connection: close
// Host: ...

void doit(int connfd);
void clientError(int fd, char *cause, char *errnum, char *shortmsg, char * longmsg);
void readRequestHeaders(rio_t *rio, int fd, int serverfd);
int parseURI(int fd, char *uri, char *port, char *serverhost, char *path);
void forwardInfo(int serverfd, int fd);
void *thread(void *argv);

void sigpipe_handler(int sig)
{
	return;
}


int main(int argc, char *argv[])
{
	int listenfd, *connfd;
	struct sockaddr_storage clientaddr;
	socklen_t clientlen;
	pthread_t tid;

	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	
	Signal(SIGPIPE, sigpipe_handler);
	listenfd = Open_listenfd(argv[1]);
	
	while(1)
	{
		clientlen = sizeof(clientaddr);
		connfd = malloc(sizeof(int));
		*connfd = Accept(listenfd, (SA*) &clientaddr, &clientlen);
		Pthread_create(&tid, NULL, thread, connfd);
	}

  return 0;
}

void *thread(void *argv)
{
	int connfd = *(int *)argv;
	Free(argv);
	Pthread_detach(Pthread_self());
	doit(connfd);
	Close(connfd);
	return NULL;
}

void doit(int connfd)
{
	rio_t rio;
	char buf[MAXLINE], method[MAXLINE] = { 0 }, uri[MAXLINE] = { 0 }, protocol[MAXLINE] = { 0 };
	int n, serverfd;
	char port[MAXLINE] = "80", path[MAXLINE] = { 0 }, serverhost[MAXLINE] = { 0 };

	rio_readinitb(&rio, connfd);
	rio_readlineb(&rio, buf, MAXLINE);
	n = sscanf(buf, "%s %s %s", method, uri, protocol);
	if(n != 3 || !method[0] || !uri[0] || !protocol[0])
	{
		clientError(connfd, buf, "400", "Bad request", "Proxy-Tiny cannot understand your request");
		return;
	}
	if(strcasecmp("GET", method))
	{
		clientError(connfd, method, "501", "Not implemented", "Proxy-Tiny does not implement this method");
		return;
	}
	
	//服务器IP和端口,路径
	if(parseURI(connfd, uri, port, serverhost, path))
	{
		return;
	}

	//连接服务器并请求服务
	serverfd = Open_clientfd(serverhost, port);
	sprintf(buf, "%s %s %s", method, path, "HTTP/1.0\r\n");
	rio_writen(serverfd, buf, strlen(buf));
	
	readRequestHeaders(&rio, connfd, serverfd);
	
	//转发信息
	forwardInfo(serverfd, connfd);
	Close(serverfd);
}

/* begin readRequestHeaders */
void readRequestHeaders(rio_t *rio, int fd, int serverfd)
{
	char buf[MAXLINE];
	char host[MAXLINE] = "Host: www.cmu.edu";

	rio_readlineb(rio, buf, MAXLINE);
	while(strcmp(buf, "\r\n"))
	{
		if(strstr(buf, "Host"))
			strcpy(host, buf);
		strcat(buf, "\r\n");
		rio_writen(serverfd, buf, strlen(buf));
		rio_readlineb(rio, buf, MAXLINE);
	}
	strcat(host, "\r\n");
	rio_writen(serverfd, host, strlen(host));
	rio_writen(serverfd, (void *) user_agent_hdr, strlen(user_agent_hdr));
	rio_writen(serverfd, (void *) connectclose, strlen(connectclose));
	rio_writen(serverfd, (void *) proxyconnect, strlen(proxyconnect));
	rio_writen(serverfd, "\r\n", strlen("\r\n"));
}
/* end readRequestHeaders */

/* begin parseURI it succeeds if return 0*/
int parseURI(int fd, char *uri, char *port, char *serverhost, char *path)
{
	/* http://www.cmu.edu:%d/index/home.html -> /index/home.html(path), %d(port), www.cmu.edu(serverhost)*/	
	char tmp[MAXLINE] = "";

	port[0] = '\0';
	serverhost[0] = '\0';
	path[0] = '\0';

	sscanf(uri, "http://%[^/]%s", serverhost, tmp);
	if(serverhost[0] == 0 || tmp[0] == 0)
	{
		clientError(fd, uri, "400", "Bad request", "Proxy-Tiny cannot understand your request");
		return 1;
	}
	strcpy(path, tmp);
	//是否给了特定的端口
	if(strstr(serverhost, ":"))
	{
		sscanf(serverhost, "%[^:]:%s", tmp, port);
		strcpy(serverhost, tmp);
		return 0;
	}
	//默认端口80
	strcpy(port, "80");
	return 0;
}
/* end parseURI */

void forwardInfo(int serverfd, int fd)
{
	rio_t rio;
	char buf[MAXLINE];
	int n;
	long cnt = 0;
	rio_readinitb(&rio, serverfd);

	while((n = rio_readlineb(&rio, buf, MAXLINE)))
	{
		printf("received %d bytes(%ld total) from Tiny\n", n, cnt += n);
		fflush(stdout);
		rio_writen(fd, (void *) buf, n);
	}
}

/* begin clienterror */
void clientError(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor=""ffffff"">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
    Rio_writen(fd, buf, strlen(buf));
}
/* end clienterror */
