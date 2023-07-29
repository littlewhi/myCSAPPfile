/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
//#include <math.h>
//extern double log2(double);

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "beef",
    /* First member's full name */
    "Yang HongBin",
    /* First member's email address */
    "3157470865@qq.com",
    /* Second member's full name (leave blank if none) */
    "NONE",
    /* Second member's email address (leave blank if none) */
    "NULL"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define PTRSIZE sizeof(int*)
#define LEN 28
/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define WSIZE 4


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))
#define MAXHEAPSIZE 0xfffffff8
#define MINHEAPSIZE 8 /* bytes, 分配的块 */
#define CONTROLPART (sizeof(int*) * 2 + 8)
#define PACK(size, alloc) ((size) | (alloc))
#define READ(p) *((unsigned int*)(p))
#define WRITE(p, val) (*((unsigned int*)(p)) = (val))
#define PUTPTR(p, val) (*(unsigned int**)(p) = (unsigned int*)(val))
#define GETLISTHEADP(i) (heapList + (i) * CONTROLPART)
#define HGETNEXT(p) ((p) + WSIZE + PTRSIZE)
#define HGETHEAD(p) (p)
#define HGETPREV(p) ((p) + WSIZE)
#define HGETFOOT(p) ((p) + HGETSIZE(p) + CONTROLPART - WSIZE)
#define HGETSIZE(p) (READ(p) & ~7)
/* 
 * mm_init - initialize the malloc package.
 * keep a array of free space lists called alist
 * the least chunk is 8 bytes except control part
 * so 
 */

void *heapList = NULL;

static unsigned int getHighBit(unsigned int n)
{
	unsigned int i;
	for(i = 31; i > 0; --i)
	{
		if((n >> i))
			break;
	}
	return i;
}

//查找空闲链表
static void* findList(size_t size, int *index)
{
	*index = getHighBit(size) - 3;
	void *listh = GETLISTHEADP(*index);
	return listh;
}
//添加块到空闲链表
static void addList(void *listh, void *bp)
{
	PUTPTR(HGETNEXT(bp), *(void**)HGETNEXT(listh));	
	PUTPTR(HGETNEXT(listh), bp);
	PUTPTR(HGETPREV(*(void**)HGETNEXT(bp)), bp);
	PUTPTR(HGETPREV(bp), listh);
}

//删除块从空闲列表
static void deleteFromList(void *bp)
{
	void *prev = *(void**)HGETPREV(bp);
	PUTPTR(HGETNEXT(prev), *(void**)HGETNEXT(bp));	
	PUTPTR(HGETPREV(*(void**)HGETNEXT(bp)), prev);
	PUTPTR(HGETPREV(bp), NULL);
	PUTPTR(HGETNEXT(bp), NULL);
}
void *extendHeap(size_t size)
{
	void *bp = NULL;
	if((bp = mem_sbrk(size + CONTROLPART)) == (void*)-1)
		return bp;
	WRITE(HGETHEAD(bp), PACK(size, 0));
	WRITE(HGETFOOT(bp), PACK(size, 0));
	return bp;
}

int mm_init(void)
{
	//初始设置长度为30的数组
  int i;
	void *head, *tail;
//	int size = ALIGNMENT;
	if((heapList = mem_sbrk(LEN * (CONTROLPART))) == (void*)-1)
		return -1;
	for(i = 0; i <= LEN; ++i)
	{
		/* 链表尾部 */
		tail = extendHeap(0);
		WRITE(HGETHEAD(tail), PACK(0, 1));
		WRITE(HGETFOOT(tail), PACK(0, 1));
		/* 链表头部 */
		head = i * (CONTROLPART) + heapList;
		
		WRITE(HGETHEAD(head), PACK(0, 1));
		PUTPTR(HGETPREV(head), 0);
		PUTPTR(HGETNEXT(head), tail);
		WRITE(HGETFOOT(head), PACK(0, 1));

		PUTPTR(HGETNEXT(tail), 0);
		PUTPTR(HGETPREV(tail), head);
	}
	return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void* findFit(void **list, int i, size_t need)
{
//	++cnt;
	while(i <= LEN)
	{
		void *bp = NULL;
		size_t size;
		for(bp = *(void**)HGETNEXT(*list); bp != NULL; bp = *(void**)HGETNEXT(bp))
		{
			size = HGETSIZE(bp);
			if(size >= need)
			{
				return bp;
			}
		}
		*list += CONTROLPART;
		++i;
	}
	return NULL;
}

void place(void *listh, void *bp, size_t size)
{
	size_t csize = HGETSIZE(bp);
	int newChuncksize;

	deleteFromList(bp);
	//printf("删除空闲块从列表 : %p, size : %u\n", listh, csize);
	//fflush(stdout);
	/* 分割 */
	if(((newChuncksize =(int) ((long long)csize - (long long)size - (long long)CONTROLPART))) >= MINHEAPSIZE)
	{
		//printf("可以分割\n");
		//fflush(stdout);
		void *newchunk = NULL;
		int index;
		void *newListh;
		newchunk = bp + size + CONTROLPART;
		/* 后半部分 */
		newListh = findList(newChuncksize, &index);
		WRITE(newchunk, PACK(newChuncksize, 0));
		WRITE(HGETFOOT(newchunk), PACK(newChuncksize, 0));
		addList(newListh, newchunk);
		
		/*前半部分*/
		WRITE(HGETHEAD(bp), PACK(size, 1));
		WRITE(HGETFOOT(bp), PACK(size, 1));
	}	
	else
	{
		WRITE(HGETHEAD(bp), PACK(csize, 1));
		WRITE(HGETFOOT(bp), PACK(csize, 1));
	}
}

void *mm_malloc(size_t size)
{
	size_t newsize = ALIGN(size + WSIZE);
	void* listh;
	int index;
	char *bp = NULL;
	listh = findList(newsize, &index);
	//printf("第%d个分配:\nsize:%u, newsize:%u, 第%d链表\n", ++cnt, size, newsize, index);
	//fflush(stdout);

	if((bp = findFit(&listh, index, newsize)) != NULL)
	{
		//printf("直接找到了合适空闲块, bp : %p\n", bp);
		//fflush(stdout);
		place(listh, bp, newsize);
		//printf("空闲块放置成功\n");
		//fflush(stdout);
		return bp + 2 * (WSIZE + PTRSIZE);
	}
	
	if((bp = extendHeap(newsize)) == (void*)-1)
		return NULL;
	//printf("获取新的空闲块, bp : %p", bp);
	//fflush(stdout);
	listh = findList(newsize, &index);
	//printf("找到新空闲块的链表,index: %d,listh: %p\n", index, listh);
	//fflush(stdout);
	addList(listh, bp);
	//printf("添加空闲块到链表成功\n");
	//fflush(stdout);
	place(listh, bp, newsize);
	//printf("放置新空闲块成功\n");
	//fflush(stdout);
	//heapsize += HGETSIZE(bp) + CONTROLPART;
	return bp + 2 * (WSIZE + PTRSIZE);
}

/*
 * mm_free - Freeing a block does nothing.
 */
#define HGETFORP(p) ((p) - HGETSIZE(HGETPFOOT(p)) - CONTROLPART)
#define HGETBACKP(p) ((p) + HGETSIZE(p) + CONTROLPART)
#define HGETPFOOT(p) ((p) - WSIZE)
#define HGETNHEAD(p) ((p) + CONTROLPART + HGETSIZE(p))
#define ISALLOC(p) (READ(p) & 7)
static void *coalesce(void *bp)
{
	int prev = ISALLOC(HGETPFOOT(bp));
	int next = 1;
	if(bp + HGETSIZE(bp) + CONTROLPART < mem_heap_hi())
		next = ISALLOC(HGETNHEAD(bp));
	void *ret = bp;
	long long s;
//	int i = 0;
	if(!prev)
	{
		ret = HGETFORP(bp);	
		//printf("prev : %p, prevsize : %u, index : %d\n",ret, HGETSIZE(ret), i);
		//fflush(stdout);
		//printf("合并空闲块 prev:%d, next:%d, bp:%p\n", prev, next, ret);
		//fflush(stdout);
		if((s = HGETSIZE(ret) + HGETSIZE(bp) + CONTROLPART) <= (unsigned long long)MAXHEAPSIZE)
		{
			//printf("删除\n");
			//fflush(stdout);
			deleteFromList(ret);
			WRITE(HGETHEAD(ret), PACK((unsigned int)s, 0));
			WRITE(HGETFOOT(ret), PACK((unsigned int)s, 0));
		}
	}
	if(!next)
	{
		void *n = HGETBACKP(ret);
		//void *l = NULL;
		if(n > mem_heap_hi() || HGETSIZE(n) == 0)
			return ret;
		//printf("next listh : %p\n", l);
		//printf("next : %p, nextsize : %u\n", n, HGETSIZE(n));
		//fflush(stdout);
	
		if((s = HGETSIZE(n) + HGETSIZE(ret) + CONTROLPART) <= (unsigned long long)MAXHEAPSIZE)
		{
			//printf("删除\n");
			//fflush(stdout);
			deleteFromList(n);
			WRITE(HGETHEAD(ret), PACK((unsigned int)s, 0));
			WRITE(HGETFOOT(ret), PACK((unsigned int)s, 0));
		}
	}
	return ret;
}

//int fcnt = 0;
void mm_free(void *ptr)
{
	void* bp = ptr - 2 * (WSIZE + PTRSIZE);
	size_t size = HGETSIZE(bp);
	int index;
	void* listh;	//printf("释放块:\nsize : %u, bp : %p\n", size, bp);
	//fflush(stdout);
	WRITE(HGETHEAD(bp), PACK(size, 0));
	WRITE(HGETFOOT(bp), PACK(size, 0));
	
	bp = coalesce(bp);
	size = HGETSIZE(bp);
	listh = findList(size, &index);
	addList(listh, bp);
	//printf("添加新释放的块到链表 listh : %p, index : %d, bpsize : %u\n", listh, index, HGETSIZE(bp));
	//fflush(stdout);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = HGETSIZE(oldptr - CONTROLPART);
   	if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}
