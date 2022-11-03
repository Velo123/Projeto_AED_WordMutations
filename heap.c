/******************************************************************************
 *
 * File Name: heap.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *
 * NAME
 *     Heap11 - Heap operations
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS tested
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

/* to remove comments, just delete or comment the next line */
#define DEMO

/* A heap is represented by a structure: */
struct _heap {
  int (*less) (Item, Item);     /* Surprise! this field is a function pointer
                                 * to elements in the heap. */
  void (*print) (Item);         /* So is this one!! */
  int n_elements;               /* # elements in heap */
  int size;                     /* max size of the heap. */
  Item *heapdata;               /* An array of Items. */
};

void (*PrintItem) (Item);

/******************************************************************************
 * PrintHeap()
 *
 * Arguments: h - pointer to heap structure
 * Returns: void
 * Side-Effects: none
 *
 * Description: auxiliary function to print heap content
 *
 *****************************************************************************/

int PrintHeap(Heap * h)
{
    int i;

    if (h->n_elements == 0) {
        printf("Heap empty.\n");
        return 0;
    }
    printf("\n");
    for (i = 0; i < h->n_elements; i++)
        printf("+----------");
    printf("+\n");
    for (i = 0; i < h->n_elements; i++)
        printf("|   %3d    ", i);
    printf("|\n");
    for (i = 0; i < h->n_elements; i++)
        printf("+----------");
    printf("+\n");
    for (i = 0; i < h->n_elements; i++) {
        printf("| ");
        h->print(h->heapdata[i]);
        printf(" ");
    }
    printf("|\n");
    for (i = 0; i < h->n_elements; i++)
        printf("+----------");
    printf("+\n");

    return h->n_elements;
}


/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int k)
{
  Item t;
  while ((k > 0) && (h->less) ((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {
#ifdef DEMO
    /* --------------------------------------------------- */
    printf("FixUp: heap[%d]: %d is smaller than offspring heap[%d]: %d\n",
           (k - 1) / 2, *((int *) (h->heapdata)[(k - 1) / 2]),
           k, *((int *) (h->heapdata)[k]));
    printf("\t=> exchange\n");
#endif
    /*---------------------------------------------------------*/
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;

#ifdef DEMO
    /* --------------------------------------------------- */
    printf("\t=> \n");
    PrintHeap(h);
#endif
    /*---------------------------------------------------------*/
    k = (k - 1) / 2;
  }

  return;
}


/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k)
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) &&
        (h->less) (h->heapdata[j], h->heapdata[j + 1])) {
      /* second offspring is greater */
      j++;
    }
    if (!(h->less) (h->heapdata[k], h->heapdata[j])) {
      /* Elements are in correct order. */

#ifdef DEMO
      /* --------------------------------------------------- */
      printf
          ("FixDown: Compare heap[%d]: %d with heap[%d]: %d => don't exchange\n",
           k, *((int *) h->heapdata[k]), j, *((int *) h->heapdata[j]));
#endif
      /*---------------------------------------------------------*/
      break;
    }
#ifdef DEMO
    /* --------------------------------------------------- */
    printf("FixDown: heap[%d]: %d is smaller than offspring heap[%d]: %d\n",
           k, *((int *) (h->heapdata)[k]), j, *((int *) (h->heapdata)[j]));
    printf("\t=> exchange\n");
#endif
    /*---------------------------------------------------------*/

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;

#ifdef DEMO
    /* --------------------------------------------------- */
    PrintHeap(h);
#endif
    /*---------------------------------------------------------*/
  }

  return;
}


/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*less) (Item, Item), void (*print) (Item))
{
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(1);
  }

  h->n_elements = 0;
  h->less = less;
  h->print = print;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));
  if (h->heapdata == ((Item *) NULL)) {
    fprintf(stderr, "Error in malloc of heap data\n");
    exit(1);
  }

  return (h);
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

void FreeHeap(Heap *h)
{
  /****************************************************
   * Insert code here
   ****************************************************/
   int i;

   for (i = 0; i < h->n_elements; i++)
      free(h->heapdata[i]);

   free(h->heapdata);
   free(h);

   return;
}

/******************************************************************************
 * Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/

int Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;
  FixUp(h, h->n_elements - 1);

  return 1;
}

/******************************************************************************
 * Direct_Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap but does not perform fixup
 *
 *****************************************************************************/

int Direct_Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;


  return 1;
}

/******************************************************************************
 * Modify()
 *
 * Arguments: h - pointer to heap
 *            index - index of element to modify
 *            newvalue - new element value
 * Returns: void
 * Side-Effects: none
 *
 * Description: compares new element with antecedent, if larger do a fixup
 *              otherwise do fixdown
 *
 *****************************************************************************/

void Modify(Heap * h, int index, Item newvalue)
{
  if (index > h->n_elements - 1) {
    printf("Index out of range (index = %d) !\n", index);
    return;
  }
  /* Compares new value  with the value of the element to substitute */
  if ((h->less) (newvalue, h->heapdata[index])) {
    /* If smaller, reconstruct heap with function FixDown */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixDown(h, index);
  }
  else {
    /* If greater, reconstruct heap using the function FixUp */
    free(h->heapdata[index]);
    h->heapdata[index] = newvalue;
    FixUp(h, index);
  }

  return;
}


/******************************************************************************
 * RemoveMax()
 *
 * Arguments: h - pointer to heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: exchange first and last element of heap, remove last element
 *              (max element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/

Item RemoveMax(Heap * h)
{
  Item t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    FixDown(h, 0);
    return t;
  }

  return NULL;
}

/******************************************************************************
 * GetIndex()
 *
 * Arguments: h - pointer to heap
 *            index - index into heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: return Item in the index-th position of the heap
 *
 *****************************************************************************/

Item GetIndex(Heap * h, int index)
{
  Item t;

  if (index > h->n_elements - 1) {
    printf("Index out of range (index = %d) !\n", index);
    return NULL;
  }

  t = (h->heapdata)[index];
  return t;
}

/******************************************************************************
 * CleanHeap()
 *
 * Arguments: Heap
 * Returns: none
 * Side-Effects: None
 *
 * Description: cleans an heap
 *
 *****************************************************************************/

void CleanHeap(Heap * h)
{

   /****************************************************
    * Insert CleanHeap code here
    ****************************************************/
   int i;

   for (i = 0; i < h->n_elements; i++)
      free(h->heapdata[i]);

   h->n_elements = 0;

   return;
}

/******************************************************************************
 * VerifyHeap()
 *
 * Arguments: Heap
 * Returns: int (1 if it is an heap; 0 otherwise)
 * Side-Effects: None
 *
 * Description: verifies if the argument satisfies the heap condition
 *
 *****************************************************************************/

int VerifyHeap(Heap * h)
{
  /****************************************************
   * Insert VerifyHeap code here
   ****************************************************/
   int status = 1, i;

   for (i = h->n_elements-1; i > 0; i--)
      if ( (h->less)(h->heapdata[(i-1)/2],h->heapdata[i]) )
         return 0;

   return status;
}

/******************************************************************************
 * HeapSort()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: sorts an heap using the heapsort algorithm
 *
 *****************************************************************************/

void HeapSort(Heap * h)
{

  /****************************************************
   * Insert Sort code here
   ****************************************************/
   int n_elem = h->n_elements;
   int top = n_elem-1;
   Item aux;

   Heapify(h);

   while( top > 0 ) {
      aux = (h->heapdata)[0];
      (h->heapdata)[0] = (h->heapdata)[top];
      (h->heapdata)[top] = aux;

      h->n_elements --;
      FixDown(h,0);
      top --;
   }

   h->n_elements = n_elem;
   PrintHeap(h);

   return;
}

/******************************************************************************
 * Heapify()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: forces the argument to be an heap
 *
 *****************************************************************************/

void Heapify(Heap * h)
{

  /****************************************************
   * Insert Heapify code here
   ****************************************************/
   int i;

   for (i = h->n_elements/2-1; i >= 0; i--)
      FixDown(h, i);


   return;
}
