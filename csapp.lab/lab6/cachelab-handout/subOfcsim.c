#include "cachelab.h"
#include "csim.h"
extern void exit(int);
extern long strtol(const char*, char **, int);
/*
 *  -h help to print the usage info
 *  -v show trace info
 *  -s <s> S = 2^s, count of sets
 *  -E <E> number of lines of per set
 *  -b <b> number of block bits
 *  -t <tracefile> the input file
**************************************************
 *  I number(hex),size(byte)
 *   M number(hex),size(byte)
 *   L number(hex),size(byte)
 *   S ..
 *   modify, load, store
 */

boolean isVisible = FALSE;
int s = -1, e = -1, b = -1;
int miss = 0, hit = 0, evic = 0;
long time = LONG_MIN; 
const char* replace[] = {
	"0000", "0001", "0010", "0011",
	"0100", "0101", "0110", "0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111"
};


boolean checkFormat(char* a)
{
	return !(strlen(a) != 2 || a[0] != '-');
}

FILE* dealArguement(int cnt, char* arg[])
{
	int i;
	char op;
	FILE *fileptr = NULL;
	i = 1;
	while(i < cnt)
	{
		if(checkFormat(arg[i]) == FALSE)
		{
			printf(ERROR1);
			exit(1);
		}
		op = arg[i][1];
		switch(op)
		{
			case 'h':
				printf(HELP);
				break;
			case 'v':
				isVisible = TRUE;
				break;
			case 's':
				++i;
				if(i == cnt)
					exit(1);
				s = (int)strtol(arg[i], NULL, 10); 
				if(s < 0)
				{
					printf("The number of Sets is not legal.\n");
					exit(1);
				}
				break;
			case 'E':
				++i;
				if(i == cnt)
					exit(1);
				e = (int)strtol(arg[i], NULL, 10);
				if(e < 0)
				{
					printf("Your number of lines of per set is not legal.\n");
					exit(1);
				}
				break;
			case 'b':
				++i;
				if(i == cnt)
					exit(1);
				b = (int)strtol(arg[i], NULL, 10);
				if(b < 0)
				{
					printf("Your number of block bits is not legal.\n");
					exit(1);
				}
				break;
			case 't':
				++i;
				if(i == cnt)
					exit(1);
				fileptr = fopen(arg[i],"r");
				if(fileptr == NULL)
				{
					printf("Your file cannot open.\n");
					exit(1);
				}
				break;
			default:
				printf(ERROR1);
				exit(1);
		}
		++i;
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


//读文件并且将将地址变为二进制,返回地址长度
int myReadFromFIle(FILE *f, char* addr, char* instruction)
{
	char address[65] = { 0 }; 
	int cnt = 0, i, ilen = 2;
	char t = fgetc(f), t_str[2] = "0";
	if(t == EOF)
		return 0;
	if(t == 'I')
		while(1)
		{
			t = fgetc(f);
			if(t == EOF)
				return 0;
			if(t == '\n')
				return -1;
		}
	
	instruction[0] = fgetc(f);
	instruction[1] = fgetc(f);//空格

	while(1)
	{
		t = fgetc(f);
		if(t == ',')
			break;
		
		instruction[ilen++] = t;
		t_str[0] = t;
		i = (int) strtol(t_str, NULL, 16);
		address[cnt++] = replace[i][0];
		address[cnt++] = replace[i][1];
		address[cnt++] = replace[i][2];
		address[cnt++] = replace[i][3];
	}

	//地址变成64位
	strcpy(addr + 64 - cnt, address);

	//处理指令','后面
	instruction[ilen++] = t;
	while(1)
	{
		t = fgetc(f);
		if(t == EOF)
			return 0;
		if(t == '\n')
			break;
		instruction[ilen++] = t;
	}

	return cnt;
}

int getSet( const char *addr)
{
	char t[64] = { 0 };	
	strncpy(t, addr + 64 - s - b, s);
	return strtol(t, NULL, 2);
}

int getLine(const char *addr)
{
	char t[64] = { 0 };
	strncpy(t, addr, 64 - s - b);
	return strtol(t, NULL, 2);
}

int getBlock(const char *addr)
{
	return 1;
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
	return i;
}

char* output[] = {
	" hit",
	" miss",
	" eviction"
};

boolean dealInstruction(myCache *cache, char *instruction, const char *address)
{
	int i, empty;
	//标记, 组, 块偏移
	//get number
	int set = getSet(address);
	int line = getLine(address);
//	int block = getBlock(len, address);
	
	myLine *lines = cache->sets[set].lines;
	empty = 0;
	for(i = 0; i < e; ++i)
	{
		if(lines[i].isValid && lines[i].flag == line )
		{
			++hit;
			lines[i].time = time;
			strcpy(instruction + strlen(instruction), output[0]);
			if(instruction[0] == 'M')
			{
				++hit;
				strcpy(instruction + strlen(instruction), output[0]);
			}
			return TRUE;
		}
		if(lines[i].isValid == FALSE)
			++empty;
	}
	//没有找到
	++miss;
	if(empty == 0) //需要替换
	{
		++evic;
		i = getLRU(lines);
		strcpy(instruction + strlen(instruction), output[1]);
		strcpy(instruction + strlen(instruction), output[2]);
	}
	else					//添加
	{
		i = getEmpty(lines);
		strcpy(instruction + strlen(instruction), output[1]);
	}
	if(instruction[0] == 'M')
	{
		++hit;
		strcpy(instruction + strlen(instruction), output[0]);
	}
	lines[i].flag = line;
	lines[i].time = time;
	lines[i].isValid = TRUE;
	return FALSE;
}

int main(int argc, char* argv[])
	/*
	 *	argc = count of arguement plus 1, because the argv[0] is the name of the program
	 *
	 */
{
		char instruction[100] = { 0 }, address[100] = { 0 };
		int cnt;
		FILE * input = dealArguement(argc, argv);
		if(s < 0 || b < 0 || e < 0 || input == NULL)
			return 0;

		myCache *cachePtr = CreateCache();
		if(cachePtr == NULL)
			return 0;
		memset(address, '0', 64);
		memset(instruction, 0, 100);

		while((cnt = myReadFromFIle(input, address, instruction)) != 0)
		{
			if(cnt == -1)
				continue;

			dealInstruction(cachePtr, instruction, address);
			if(isVisible == TRUE)
			{
				puts(instruction);
			}

			++time;
			memset(address, '0', 64);
			memset(instruction, 0, 100);
	
		}
		destoryCache(cachePtr);
	
		printSummary(hit, miss, evic);
    return 0;
}
