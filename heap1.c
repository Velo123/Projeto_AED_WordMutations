#include"heap1.h"

//inciar fila
heap* iniheap(int size){    
    heap* h;

    h=(heap *) malloc(sizeof(heap));
    if (h==NULL) {
        return NULL;
    }
    h->n_elements=0;
    h->cap=size;
    h->heappos=(int*)malloc((size)*sizeof(int));
    if (h->heappos==NULL) {
        free(h);
        return NULL;
    }
    h->hn=(heapnode**)calloc(size,sizeof(heapnode*));
    if (h->hn==NULL) {
        free(h->heappos);
        free(h);
        return NULL;
    }
    return h;
}

//inserir elemento na fila e coloccar no sitio certo de acordo com a prioridade
void heapinsert(heap* h,heapnode* fn)
{
    h->hn[h->n_elements]=fn;
    h->heappos[fn->v]=h->n_elements;
    h->n_elements++;
    fixup(h,fn->v);
    return;
}

//atualizar prioridade do vertice k dentro da fila
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

//printar fila
void heapprint(heap* h){
    printf("---------\n");
    for (int i = 0; i < h->n_elements; i++)
    {
        printf("%d %d\n",h->hn[i]->v,h->hn[i]->w);
    }
    printf("---------\n");
    return;
}

//retirar elemento da fila. colocar tudo no sitio certo e atualizar as suas posicoes dentro da fila
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


//arrnjar fila de cima para baixo
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

//limpar fila
void clearfila(heap* h){
    while (h->n_elements!=0)
    {
        pop(h);
    }
}

//libertar fila
void ffreefila(heap* h){
    free(h->hn);
    free(h->heappos);
    free(h);
}