#include"heap1.h"

heap* iniheap(int size){
    heap* h;

    h=(heap *) malloc(sizeof(heap));
    if (h==NULL) {
        fprintf(stderr, "Error in malloc of heap\n");
        exit(1);
    }

    h->n_elements=0;
    h->size=size;
    h->heapdata=(int*)malloc(size*sizeof(int));
    if (h->heapdata==NULL) {
        fprintf(stderr, "Error in malloc of heap\n");
        exit(1);
    }
    
    return h;
}

void heapinsert(heap* h,int v)
{
    h->heapdata[h->n_elements] = v;
    h->n_elements++;
    fixup(h, h->n_elements - 1);
}


void fixup(heap* h,int k){
    int t=0;
    while ((k > 0) && ((h->heapdata)[(k - 1) / 2]<(h->heapdata)[k])){
        t = (h->heapdata)[k];
        (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
        (h->heapdata)[(k - 1) / 2] = t;
        k = (k - 1) / 2;
    }
}

void fixdown(heap* h,int k){
    int j,t;
    while ((2 * k + 1) < h->n_elements) {
        j = 2 * k + 1;
        if (((j + 1) < h->n_elements) && (h->heapdata[j]<h->heapdata[j + 1])) { 
            j++;
        }
        if (h->heapdata[k]<h->heapdata[j]) {
            break;
        }
        t = (h->heapdata)[k];
        (h->heapdata)[k] = (h->heapdata)[j];
        (h->heapdata)[j] = t;
        k = j;
    }
}

void heapprint(heap* h){
    printf("---------\n");
    for (int i = 0; i < h->n_elements; i++)
    {
        printf("%d\n",h->heapdata[i]);
    }
    printf("---------\n");
    
}

int removemax(heap * h)
{
  int t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    //free(h->heapdata[h->n_elements - 1]);
    h->n_elements--;
    fixdown(h, 0);
    return t;
  }

  return -1;
}

void Heapify(heap * h)
{

  /****************************************************
   * Insert Heapify code here
   ****************************************************/
   int i;

   for (i = h->n_elements/2-1; i >= 0; i--)
      fixdown(h, i);


   return;
}