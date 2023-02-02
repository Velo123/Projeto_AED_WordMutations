#include"graphf.h"
#define maxWT 1000000


typedef struct edges
{
    int w;  //peso de aresta
    int v;  //vertice de aresta
    edge* next;
}edges;



//funcao para criar grafo
graph* creategraph(int graphsize){
    graph* g=(graph*)malloc(sizeof(graph));     //alocar memoria para grafo
    g->g=(edge**)calloc(graphsize,sizeof(edge*));   //alocar memoria para lista de adjacencias
    g->nv=graphsize;    //guardar numero de vertices
    
    return g;   //retornar grafo
}

//funcao para adicionar aresta
void addedge(edge** gp,int pos,int w,int v){
    edge* temp;
    if(gp[pos]==NULL){  //se a lista de adjacencias estiver vazia
        gp[pos]=(edge*)malloc(sizeof(edge));    //alocar memoria para aresta
        gp[pos]->w=w;   //guardar peso
        gp[pos]->v=v;   //guardar vertice
        gp[pos]->next=NULL; //guardar ponteiro para proximo elemento
    }
    else    //se a lista de adjacencias nao estiver vazia - adicionar aresta no inicio da lista
    {
        temp=gp[pos];   //guardar cabeca de lista
        gp[pos]=(edge*)malloc(sizeof(edge));    //alocar memoria para aresta
        gp[pos]->w=w;   //guardar peso
        gp[pos]->v=v;   //guardar vertice
        gp[pos]->next=temp; //guardar ponteiro para proximo elemento
    }
    
}

//funcao para libertar a memoria ocupada pelo grafo
void freegraph(graph* gi){
    edge* temp1;
    for (int i = 0; i < gi->nv; i++)
    {
        while(gi->g[i]!=NULL){
            temp1=gi->g[i];
            gi->g[i]=gi->g[i]->next;
            free(temp1);
        }
    }
    free(gi->g);
    free(gi);
}

//retornar cabeca de lista de adjacencias de um vertive
edge* getgraphhead(edge** g,int pos){
    return g[pos];
}

//retornar proximo elemento adjacente da lista
edge* getgraphnext(edge* e){
    return e->next;
}

//retornar vertice de aresta
int getv(edge* e){
    return e->v;
}

//retornar peso da aresta
int getw(edge* e){
    return e->w;
}

//procurar no grafo
int dijkstra(graph *g, int s,heapnode* fn,int max,int d)
{
    int v; 
    edge* t;

    heap* h=iniheap(g->nv); //inicar pilha
    if (h==NULL)
    {
        return -1;
    }
    
    heapnode* temp; //guardar elemento retirado da heap temporariamente

    fn[s].w=0;  //inicializar custo de partida
    heapinsert(h,&fn[s]); //colocar na heap elemento de partida
    int c;
    while (h->n_elements!=0)    //enquanto a heap nao estiver vazia
    {
        temp=pop(h); //retirar elemento prioritario
        
        if (temp->w != maxWT)   //so o elemento retirado da heap se nao tiver sido visitado
        {
            v=temp->v;  //guardar vertice de onde veio
            c=temp->w;  //guardar custo de onde veio
            for (t = g->g[v]; t != NULL; t = t->next)   //percorrer lista de adjacencias do vertice retirado da heap
            { 
                if (fn[t->v].visited==1 || t->w>max){continue;} //verificar se vertice da aresta ja foi visitado. se ja, nao colocar na fila
                if (fn[t->v].w==maxWT)  //ainda nao foi visitado: atualizar o custo e colocar na fila p/ ser visitado
                {
                    fn[t->v].w=(t->w)*(t->w)+c; //atualizar custo
                    fn[t->v].from=v;    //atualizar de onde veio
                    heapinsert(h,&fn[t->v]);    //colocar na fila p/ ser visitado
                }
                
                else if (fn[t->v].w > (t->w)*(t->w)+c)  //encontrado novo custo menor para t->v: atualizar de onde vem e quanto custa e atulizar a sua prioridade na fila
                {
                    fn[t->v].w=(t->w)*(t->w)+c; //atualizar custo
                    fn[t->v].from=v;    //atualizar de onde veio
                    fixup(h,t->v);  //atualizar prioridade na fila
                }
            }
            temp->visited=1;    //colocar vertice como visitado
            if (v==d)   //assim que chega ao vertice de destino: libertar memoria de fila e retornar 1
            {
                ffreefila(h);   //libertar memoria de fila
                return 1;
            }
        }
    }
    //se chegar aqui: caminho inexistente
    ffreefila(h);   //libertar memoria de fila
    return 0;   //retornar 0: caminho inexistente
}