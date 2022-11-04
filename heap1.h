#ifndef heap1
#define heap1

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct _heap heap;
typedef struct _heapnode heapnode;

struct _heapnode
{
    int v;
    int w;
    int from;
    int visited;
};


struct _heap {
    int n_elements;
    int cap;
    int* heappos;
    heapnode** hn;
};
void ffreefila(heap* h);
heap* iniheap(int size);
void fixup(heap* h,int k);
void heapinsert(heap* h,heapnode* fn);
void fixdown(heap* h,int k);
void heapprint(heap* h);
heapnode* pop(heap* h);
void clearfila(heap* h);
#endif