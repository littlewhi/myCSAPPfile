#include "csapp.h"
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

typedef struct cacheObj
{
	struct cacheObj *prev, *next;
	char name[MAXLINE];
	char *content;
	int size;
}cacheObj, *cache_t;

void init_C();
cache_t createCache();
int findCacheObj(char *name, char *ret, int *size);
int renewCache(char *name, char *content, int size);
void destory();
