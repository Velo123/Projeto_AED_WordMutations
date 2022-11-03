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
};

heap* iniheap(int size);
void fixup(heap* h,int k);
void heapinsert(heap* h,int v);
int removemax(heap * h);
void fixdown(heap* h,int k);
void heapprint(heap* h);

#endif