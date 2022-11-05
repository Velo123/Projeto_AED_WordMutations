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
    graph* g=(graph*)malloc(sizeof(graph));
    g->g=(edge**)calloc(graphsize,sizeof(edge*));
    g->nv=graphsize;
    
    return g;
}

//funcao para adicionar aresta
void addedge(edge** gp,int pos,int w,int v){
    edge* temp;
    if(gp[pos]==NULL){
        gp[pos]=(edge*)malloc(sizeof(edge));
        gp[pos]->w=w;
        gp[pos]->v=v;
        gp[pos]->next=NULL;
    }
    else
    {
        temp=gp[pos];
        gp[pos]=(edge*)malloc(sizeof(edge));
        gp[pos]->w=w;
        gp[pos]->v=v;
        gp[pos]->next=temp;
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
    
    heapnode* temp;

    fn[s].w=0;
    heapinsert(h,&fn[s]); //colocar na heap elemento de partida
    int c;
    while (h->n_elements!=0)
    {
        temp=pop(h); //retirar elemento prioritario
        
        if (temp->w != maxWT)
        {
            v=temp->v;
            c=temp->w;
            for (t = g->g[v]; t != NULL; t = t->next)
            { 
                if (fn[t->v].visited==1 || t->w>max){continue;} //verificar se vertice da aresta ja foi visitado. se ja, nao colocar na fila
                if (fn[t->v].w==maxWT)  //ainda nao foi visitado: atualizar o custo e colocar na fila p/ ser visitado
                {
                    fn[t->v].w=(t->w)*(t->w)+c;
                    fn[t->v].from=v;
                    heapinsert(h,&fn[t->v]);
                }
                
                else if (fn[t->v].w > (t->w)*(t->w)+c)  //encontrado novo custo menor para t->v: atualizar de onde vem e quanto custa e atulizar a sua prioridade na fila
                {
                    fn[t->v].w=(t->w)*(t->w)+c;
                    fn[t->v].from=v;
                    fixup(h,t->v);
                }
            }
            temp->visited=1;    //colocar vertice como visitado
            if (v==d)   //assim que chega ao vertice de destino: libertar memoria de fila e retornar 1
            {
                ffreefila(h);
                return 1;
            }
        }
    }
    ffreefila(h);
    return 0;   //retornar 0: caminho inexistente
}