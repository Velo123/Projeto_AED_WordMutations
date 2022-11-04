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
    h->heappos=(int*)malloc((size)*sizeof(int));
    
    return h;
}

void heapinsert(heap* h,int v)
{
    
    h->heappos[v]=h->n_elements;
    h->heapdata[h->n_elements] = v;
    h->n_elements++;
    fixup(h, h->n_elements - 1);
    return;
}

void trade(heap* h,int v1,int v2,int p1, int p2){
    h->heappos[v1]=p2;
    h->heappos[v2]=p1;
    return;
}

void fixup(heap* h,int k){
    int t=0;
    while ((k > 0) && ((h->heapdata)[(k - 1) / 2]<(h->heapdata)[k])){
        t = (h->heapdata)[k];
        (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
        (h->heapdata)[(k - 1) / 2] = t;
        trade(h,t,(h->heapdata)[k],k,(k - 1) / 2);
        k = (k - 1) / 2;
    }
    return;
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
    return;
}


void heapfree(heap* h){
    free(h->heapdata);
    free(h->heappos);
    free(h);
    return;
}


int removemax(heap * h)
{
  int t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    h->n_elements--;
    fixdown(h, 0);
    return t;
  }

  return -1;
}