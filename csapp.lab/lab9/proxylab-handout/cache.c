#include "cache.h"

/* 
 * 创建
 * 查找
 * 更新
 * 销毁
 */

static cache_t list;
static sem_t mutex;
static int nread;
static sem_t w;
static int cnt;

void init_C()
{
	Sem_init(&mutex, 0, 1);
	nread = 0;
	Sem_init(&w, 0, 1);
	cnt = 0;
}

/* create */
cache_t createCache()
{
	list = Malloc(sizeof(cacheObj));
	list->prev = list;
	list->next = list;
	list->content = NULL;
	list->size = 0;
	return list;
}

static void deleteNode(cacheObj *c)
{
	c->next->prev = c->prev;
	c->prev->next = c->next;
	c->next = NULL;
	c->prev = NULL;
}

static void addFirst(cacheObj *c)
{
	c->next = list->next;
	list->next = c;
	c->prev = list;
	list->next->prev = c;
}

/* find */
int findCacheObj(char *name, char *ret, int *size)
{
	cacheObj *c;
	
	P(&mutex);
	if(++nread == 1)
	{
		P(&w);
	}
	for(c = list->next; c->size; c = c->next)
	{
		if(strcmp(c->name, name) == 0)
		{
			memcpy(ret, c->content, c->size);
			*size = c->size;
			deleteNode(c);
			addFirst(c);
			break;
		}
	}
	if(--nread == 0)
	{
		V(&w);
	}
	V(&mutex);
	if(c->size == 0)
		return 1;
	return 0;
}

/* renew */
int renewCache(char *name, char *content, int size)
{
	cacheObj *p;


	P(&w);
	
	if(cnt > MAX_CACHE_SIZE)
	{
		p = list->prev;
		deleteNode(p);
		Free(p->content);
		Free(p);
		--cnt;
	}
	++cnt;
	p = Malloc(size);
	p->prev = NULL;
	p->next = NULL;
	p->size = size;
	p->content = Malloc(size);
	strcpy(p->name, name);
	memcpy(p->content, content, size);
	addFirst(p);

	V(&w);
	return 0;
}

/* destory */
void destory()
{
	cacheObj *c, *nc;	
	for(c = list->next; c->size;)
	{
		nc = c->next;
		Free(c->content);
		Free(c);
		c = nc;
	}
	Free(list);
}
