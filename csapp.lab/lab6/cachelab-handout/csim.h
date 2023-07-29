#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0
#define ERROR1 "Your arguament is not legal.\n"
#define HELP "-h help to print the usage info\n-v show trace info\n-s <s> S = 2^s, count of sets\n-E <E> number of lines of per set\n-b <b> number of block bits\n-t <tracefile> the input file\n"
#define ADDRLEN 64

typedef int boolean;

typedef struct
{
	int cap;
	boolean isValid;
	int flag;
	long time;
}myLine;

typedef struct
{
	int cap;
	myLine *lines;
}mySet;

typedef struct
{
	int cap;
	mySet *sets;
}myCache;

typedef struct
{
	char op;
	unsigned long a;
	int s;
}instruction;
