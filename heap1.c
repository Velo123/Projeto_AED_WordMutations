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
    h->st=(int*)malloc((size)*sizeof(int));
    h->wt=(int*)malloc((size)*sizeof(int));
    return h;
}

int heapi(heap* h,int v){
    h->heapdata[h->n_elements]=v;
    h->heappos[v]=h->n_elements;
    h->n_elements++;

    
}












/*void heapinsert(heap* h,int v)
{
    h->heappos[v]=h->n_elements;
    h->heapdata[h->n_elements] = v;
    h->n_elements++;
    fixup(h,v);
    return;
}

void trade(heap* h,int v1,int v2){

    int pfv1=h->heappos[v1];
    //int pfv2=h->heappos[v2];

    h->heappos[v1]=h->heappos[v2];
    h->heappos[v2]=pfv1;

    return;
}

void fixup(heap* h,int k){
    int t=0;
    int idx=h->heappos[k];
    while ((idx > 0) && h->wt[k]<h->wt[(h->heapdata[(idx-1)/2])])
    {

        //printf("%d %d %d %d %d %d\n",k,(h->heappos)[(h->heapdata)[k]],(h->heapdata)[k],(k - 1) / 2,(h->heappos)[(h->heapdata)[(k - 1) / 2]],(h->heapdata)[(k - 1) / 2]);

        trade(h,k,h->heapdata[(idx-1)/2]);

        //printf("%d %d %d %d %d %d\n",k,(h->heappos)[(h->heapdata)[k]],(h->heapdata)[k],(k - 1) / 2,(h->heappos)[(h->heapdata)[(k - 1) / 2]],(h->heapdata)[(k - 1) / 2]);

        t = (h->heapdata)[idx];

        (h->heapdata)[idx] = (h->heapdata)[(idx-1)/2];
        
        (h->heapdata)[(idx-1)/2] = t;
        
        idx = (idx - 1) / 2;
    }
    return;
}



void fixdown(heap* h,int k){
    int j,t;

    while ((2 * k + 1) < h->n_elements) {
        j = 2 * k + 1;

        if (((j + 1) < h->n_elements) && (h->wt[h->heapdata[j]]<h->wt[h->heapdata[j+1]])){ 
            j++;
        }
        if (h->wt[h->heapdata[k]]>h->wt[h->heapdata[j]]) {
            break;
        }
        trade(h,h->heapdata[k],h->heapdata[j]);
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

void trade2(heap* h,int v1,int v2){

    int pfv1=h->heappos[v1];
    //int pfv2=h->heappos[v2];

    h->heappos[v1]=-1;
    h->heappos[v2]=pfv1;

    return;
}

int removemax(heap * h)
{
  int t;

  if (h->n_elements > 0) {
    //trade(h,h->heapdata[0],h->heapdata[(h->n_elements)-1]);
    
    
    trade2(h,(h->heapdata)[0],(h->heapdata)[h->n_elements - 1]);
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    h->n_elements--;
    fixdown(h, 0);
    return t;
  }

  return -1;
}*/