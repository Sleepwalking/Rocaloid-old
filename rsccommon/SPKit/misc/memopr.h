#ifndef MEMOPR_H
#define MEMOPR_H
#include <stdlib.h>
#include <stdio.h>
//#define MEMCHECK
inline void* mem_malloc(int size)
{
#ifdef MEMCHECK
	static int mallocnum = 0;
	mallocnum ++;
#endif
	void* ret = malloc(size);
#ifdef MEMCHECK
	printf("malloc\t%d\t%d\n", (unsigned int)ret, mallocnum);
#endif
	return ret;
}
inline void mem_free(void* memptr)
{
#ifdef MEMCHECK
	static int freenum = 0;
	freenum ++;
	printf("free\t%d\t%d\n", (unsigned int)memptr, freenum);
#endif
	free(memptr);
}
#endif