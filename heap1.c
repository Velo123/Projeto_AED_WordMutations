#include"heap1.h"

//inciar fila
heap* iniheap(int size){    
    heap* h;
    h=(heap *) malloc(sizeof(heap));    //alocar memoria para a fila
    if (h==NULL) {
        return NULL;
    }
    h->n_elements=0;    //inicializar numero de elementos a 0
    h->cap=size;    //inicializar capacidade maxima da fila - neste caso sera o nr de vertices de cada grafo
    h->heappos=(int*)malloc((size)*sizeof(int));    //alocar memoria para vetor de posicoes
    if (h->heappos==NULL) {
        free(h);
        return NULL;
    }
    h->hn=(heapnode**)calloc(size,sizeof(heapnode*));   //alocar memoria para vetor de ponteiros para os elementos da fila
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
    h->hn[h->n_elements]=fn;    //colocar elemento na ultima posicao da fila
    h->heappos[fn->v]=h->n_elements;    //guardar posicao do elemento na fila
    h->n_elements++;    //aumentar numero de elementos na fila
    fixup(h,fn->v); //arranjar fila de baixo para cima - colocar elemento no sitio certo conforme a prioridade
    return;
}

//atualizar prioridade do vertice k dentro da fila
void fixup(heap* h,int k){
    int idx=h->heappos[k];  //posicao do vertice k na fila
    heapnode* t;
    while ((idx>0) && (h->hn[idx]->w<h->hn[(idx-1)/2]->w))  //enquanto o vertice k tiver prioridade maior que o seu pai
    {
        h->heappos[k]=h->heappos[h->hn[(idx-1)/2]->v];  //atualizar posicao do vertice k na fila para a posicao do seu pai
        h->heappos[h->hn[(idx-1)/2]->v]=idx;    //atualizar posicao do vertice pai na fila para a posicao do k
        t=h->hn[idx];   
        h->hn[idx]=h->hn[(idx-1)/2];    //trocar de posicao com o seu pai
        h->hn[(idx-1)/2]=t; //trocar de posicao com o seu pai
        idx=(idx-1)/2;  //avancar para o novo pai
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
    if (h->n_elements>0)    //se a fila nao estiver vazia
    {
        t=h->hn[0]; //guardar o elemento que vai ser retirado

        h->heappos[t->v]=-1;    //atualizar posicao do elemento retirado para -1 - nao esta na fila
        h->heappos[h->hn[h->n_elements-1]->v]=0;    //atualizar posicao do ultimo elemento(menos prioritario) da fila para 0 - esta na posicao 0 da fila - 

        h->hn[0]=h->hn[h->n_elements-1];    //colocar o elemento menos prioritario na posicao 0 da fila e arranjar a fila de baixo para cima
        
        h->n_elements--;    //diminuir numero de elementos na fila

        fixdown(h,0);   //arranjar fila de baixo para cima
        return t;   //retornar elemento retirado
    }
    return NULL;
}


//arrnjar fila de cima para baixo
void fixdown(heap* h,int k){
    int idxc;
    while ((2*k+1)<h->n_elements){  //enquanto o vertice k tiver filhos
        idxc=2*k+1; //indice do filho esquerdo
        if(((idxc+1)<h->n_elements) && (h->hn[idxc]->w>h->hn[idxc+1]->w))   //se o filho direito for mais prioritario que o filho esquerdo
        {
            idxc++; //analisar indice do filho direito
        }
        if (h->hn[k]->w<h->hn[idxc]->w) //se o vertice k for mais prioritario que o seu filho mais prioritario
        {
            break;  //parar - fila esta arranjada
        }
        int v1=h->hn[k]->v; //guardar vertices em variaveis temporarias
        int v2=h->hn[idxc]->v;  //guardar vertices em variaveis temporarias


        h->heappos[v1]=idxc;    //atualizar posicoes dos vertices na fila
        h->heappos[v2]=k;   //atualizar posicoes dos vertices na fila

        heapnode* t=h->hn[k];
        h->hn[k]=h->hn[idxc];   //trocar de posicao com o seu filho mais prioritario
        h->hn[idxc]=t;  //trocar de posicao com o seu filho mais prioritario
        k=idxc; //avancar para o novo filho
        
    }   
}

//limpar fila
void clearfila(heap* h){    //retirar todos os elementos da fila
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