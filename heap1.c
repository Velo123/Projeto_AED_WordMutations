#include"heap1.h"


heap* iniheap(int size){
    heap* h;

    h=(heap *) malloc(sizeof(heap));
    if (h==NULL) {
        fprintf(stderr, "Error in malloc of heap\n");
        exit(1);
    }
    h->n_elements=0;
    h->cap=size;
    h->heappos=(int*)malloc((size)*sizeof(int));
    h->hn=(heapnode**)calloc(size,sizeof(heapnode*));
    return h;
}

void heapinsert(heap* h,heapnode* fn)
{
    h->hn[h->n_elements]=fn;
    h->heappos[fn->v]=h->n_elements;
    h->n_elements++;
    fixup(h,fn->v);
    return;
}

void fixup(heap* h,int k){
    int idx=h->heappos[k];
    heapnode* t;
    while ((idx>0) && (h->hn[idx]->w<h->hn[(idx-1)/2]->w))
    {
        h->heappos[k]=h->heappos[h->hn[(idx-1)/2]->v];
        h->heappos[h->hn[(idx-1)/2]->v]=idx;
        t=h->hn[idx];
        h->hn[idx]=h->hn[(idx-1)/2];
        h->hn[(idx-1)/2]=t;
        idx=(idx-1)/2;
    }
    return;
}

void heapprint(heap* h){
    printf("---------\n");
    for (int i = 0; i < h->n_elements; i++)
    {
        printf("%d %d\n",h->hn[i]->v,h->hn[i]->w);
    }
    printf("---------\n");
    return;
}

heapnode* pop(heap* h){
    heapnode* t;
    if (h->n_elements>0)
    {
        t=h->hn[0];

        h->heappos[t->v]=-1;
        h->heappos[h->hn[h->n_elements-1]->v]=0;

        h->hn[0]=h->hn[h->n_elements-1];
        
        h->n_elements--;

        fixdown(h,0);
        return t;
    }
    return NULL;
}

void fixdown(heap* h,int k){
    int idxc;
    while ((2*k+1)<h->n_elements){
        idxc=2*k+1;
        if(((idxc+1)<h->n_elements) && (h->hn[idxc]->w>h->hn[idxc+1]->w))
        {
            idxc++;
        }
        if (h->hn[k]->w<h->hn[idxc]->w)
        {
            break;
        }
        int v1=h->hn[k]->v;
        int v2=h->hn[idxc]->v;


        h->heappos[v1]=idxc;
        h->heappos[v2]=k;

        heapnode* t=h->hn[k];
        h->hn[k]=h->hn[idxc];
        h->hn[idxc]=t;
        k=idxc;
        
    }   
}

void clearfila(heap* h){
    while (h->n_elements!=0)
    {
        pop(h);
    }
}
void ffreefila(heap* h){
    free(h->hn);
    free(h->heappos);
    free(h);
}