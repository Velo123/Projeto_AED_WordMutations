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

int Insert(heap* h,int v)
{
  /*if (h->n_elements == h->size) {
    printf("Heap full (size = %d) !\n", h->size);
    return 0;
  }*/
  h->heapdata[h->n_elements] = v;

  h->n_elements++;
  fixup(h, h->n_elements - 1);

  return 1;
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