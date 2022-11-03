
/******************************************************************************
 *
 * File Name: heap.h
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 * NAME
 *     heap.h - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

typedef void *Item;

typedef struct _heap Heap;

Heap *NewHeap(int tamanho, int (*less) (Item, Item), void (*print) (Item));

void FreeHeap(Heap * h);

int Insert(Heap * h, Item element);

int Direct_Insert(Heap * h, Item element);

void Modify(Heap * h, int indice, Item newvalue);

Item RemoveMax(Heap * h);

Item GetIndex(Heap * h, int index);

int PrintHeap(Heap * h);

void CleanHeap(Heap * h);

int VerifyHeap(Heap * h);

void HeapSort(Heap * h);

void Heapify(Heap * h);