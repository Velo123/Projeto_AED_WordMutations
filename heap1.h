#ifndef heap1
#define heap1

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


typedef struct _heap heap;

struct _heap {
    int n_elements;
    int size;
    int* heapdata;
    int* heappos;
};

void heapfree(heap* h);
heap* iniheap(int size);
void fixup(heap* h,int k);
void heapinsert(heap* h,int v);
int removemax(heap * h);
void fixdown(heap* h,int k);
void heapprint(heap* h);
void trade(heap* h,int v1,int v2);
#endif