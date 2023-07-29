#include "cachelab.h"
#include "csim.h"
#include <getopt.h>
extern void exit(int);
extern long strtol(const char*, char **, int base);

boolean isVisible = FALSE;
int s = -1, e = -1, b = -1;
int miss = 0, hit = 0, evic = 0;
long time = LONG_MIN; 

FILE* dealArguement(int cnt, char* arg[])
{
	char op;
	FILE *fileptr = NULL;
	while((op = (char)getopt(cnt, arg, "hvs:E:b:t:")) != -1)
	{
		switch(op)
		{
			case 'h':
				printf(HELP);
				break;
			case 'v':
				isVisible = TRUE;
				break;
			case 's':
				s = atoi(optarg); 
				break;
			case 'E':
				e = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				fileptr = fopen(optarg,"r");
				break;
			default:
				printf(ERROR1);
				exit(1);
		}
	}	
	return fileptr;
}

myCache* CreateCache()
{
	int i, j;
	myCache* c = (myCache*) malloc(sizeof(myCache));
	if(c == NULL)
		return NULL;
	c->cap = 1 << s;

	c->sets = (mySet*) malloc(sizeof(mySet) * (1 << s));
	if(c->sets == NULL)
		return NULL;
	for(i = 0; i < 1 << s; ++i)
	{
		myLine *lines = NULL;
		c->sets[i].cap = e;
		lines = (myLine*) malloc(sizeof(myLine) * (e));
		if(lines == NULL)
			return NULL;
		for(j = 0; j < e; ++j)
		{
			lines[j].cap = 1 << b;
			lines[j].flag = -1;
			lines[j].isValid = FALSE;
			lines[j].time = LONG_MIN;
		}
		c->sets[i].lines = lines;
	}
	return c;
}

void destoryCache(myCache *c)
{
	int i;
	for(i = 0; i < (1 << s); ++i)
	{
		free(c->sets[i].lines);
	}
	free(c->sets);
	free(c);
	c = NULL;
}


//读文件并且将将地址变为二进制, n(n > 0) - 有效指令, 0 - 无效指令, -1 - 结束
int myReadFromFIle(FILE *f,char *addr, instruction *i)
{
	int end;
	if(f == NULL)
		return -1;
	end = fscanf(f, " %c %lx,%d", &(i->op), &(i->a), &(i->s));
	if(i->op == 'I')
		return 0;

	for(int j = 0; j < 64; ++j)
	{
		addr[63 - j] = ((i->a >> j) & 1) + '0';
	}
	return end;
}

int getSet(const char *addr)
{
	char t[ADDRLEN] = { 0 };	
	strncpy(t, addr + ADDRLEN - s - b, s);
	return strtol(t, NULL, 2);
}

int getLine(const char *addr)
{
	char t[ADDRLEN] = { 0 };
	strncpy(t, addr, ADDRLEN - s - b);
	return strtol(t, NULL, 2);
}

int getLRU(myLine *lines)
{
	int i;
	int ret;
	long minTime = LONG_MAX;
	for(i = 0; i < e; ++i)
	{
		if(minTime > lines[i].time)
		{
			minTime = lines[i].time;
			ret = i;
		}
	}
	return ret;
}

int getEmpty(myLine *lines)
{
	int i;
	for(i = 0; i < e; ++i)
	{
		if(lines[i].isValid == FALSE)
			break;
	}
	return i < e ? i : -1;
}

char* output[] = {
	" hit",
	" miss",
	" eviction"
};

void cacheOperate(myCache *c, int set, int flag, char *show)
{
	boolean ishit = FALSE;
	int i;
	myLine* lines = c->sets[set].lines;
	for(i = 0; i < e; ++i)
	{
		if(lines[i].isValid == TRUE && lines[i].flag == flag)
		{
			strcpy(show + strlen(show), output[0]);
			++hit;
			ishit = TRUE;
			lines[i].time = time;
		}
	}

	if(ishit == FALSE)
	{
		strcpy(show + strlen(show), output[1]);
		++miss;
		i = getEmpty(lines);
		if(i == -1)
		{
			strcpy(show + strlen(show), output[2]);
			++evic;
			i = getLRU(lines);
		}
		lines[i].time = time;
		lines[i].flag = flag;
		lines[i].isValid = TRUE;
	}
}

void process(FILE *f, myCache *c)
{
	int end;
	instruction i;
	char addr[65] = { 0 };
	char show[100] = { 0 };
	memset(&i, 0, sizeof(i));
	
	while((end = myReadFromFIle(f, addr, &i)) != -1)
	{
		if(end == 0)
			continue;
		
		int set = getSet(addr);
		int lineFlag = getLine(addr);
		
		switch(i.op)
		{
			case 'M':
				cacheOperate(c, set, lineFlag, show);
			case 'L':
			case 'S':
				cacheOperate(c, set, lineFlag, show);
				break;
			default:
				break;
		}
		++time;
		if(isVisible == TRUE)
		{
			printf("%c %lx,%d %s\n", i.op, i.a, i.s, show);
		}
		memset(show, 0, sizeof(show));
	}
}

int main(int argc, char* argv[])
{
		FILE * input = dealArguement(argc, argv);
		if(s < 0 || b < 0 || e < 0 || input == NULL)
			return 0;

		myCache *cachePtr = CreateCache();
		if(cachePtr == NULL)
			return 0;
	
		process(input, cachePtr);

		destoryCache(cachePtr);
		fclose(input);	
		printSummary(hit, miss, evic);
    return 0;
}
