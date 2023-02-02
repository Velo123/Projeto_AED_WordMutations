#ifndef heap1
#define heap1

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct _heap heap;
typedef struct _heapnode heapnode;

struct _heapnode
{
    int v;  //vertice atual
    int w;  //peso total ate este vertice
    int from;   //vertice anterior
    int visited;    //se ja foi visitado
};


struct _heap {
    int n_elements; //numero de elementos atualmente na fila
    int cap;    //capacidade maxima da fila - neste caso sera o nr de vertices
    int* heappos;   //posicao do vertice na fila
    heapnode** hn;  //vetor de ponteiros para os elementos da fila - ou seja, fila propriamente dita
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