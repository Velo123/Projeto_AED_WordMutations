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
void heapify(heap * h);
void trade2(heap* h,int v1,int v2);
void heapfree(heap* h);
heap* iniheap(int size);
void fixup(heap* h,int k);
void heapinsert(heap* h,heapnode* fn);
int removemax(heap * h);
void fixdown(heap* h,int k);
void heapprint(heap* h);
void trade(heap* h,int v1,int v2);
int VerifyHeap(heap * h);
heapnode* pop(heap* h);
#endif