#include"graphf.h"
#define P (h->wt[v] + t->w)
#define maxWT 1000000

typedef struct edges
{
    int w;
    int v;
    edge* next;
}edges;


graph* creategraph(int graphsize){
    graph* g=(graph*)malloc(sizeof(graph));
    g->g=(edge**)calloc(graphsize,sizeof(edge*));
    g->nv=graphsize;
    
    return g;
}


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

edge* getgraphhead(edge** g,int pos){
    return g[pos];
}

edge* getgraphnext(edge* e){
    return e->next;
}

int getv(edge* e){
    return e->v;
}

int getw(edge* e){
    return e->w;
}


void dijkstra(graph *g, int s,heap* h)
{
    int v, w; 
    edge* t;
    
    for (int i = 0; i < g->nv; i++)
    {
        h->st[i]=-1;
        h->wt[i]=maxWT;
        h->heappos[i]=-1;
    }
    
    heapinsert(h,s);
    
    h->st[s] = -1;
    h->wt[s] = 0;
    
    while (h->n_elements!=0)
    {   
        if (h->wt[v = removemax(h)] != maxWT)
        {
            for (t = g->g[v]; t != NULL; t = t->next)
            {
                //if(h->heappos[t->v]==-1){heapinsert(h,t->v);}    //verificar se esta ou esteve na fila
                if(h->wt[t->v]==maxWT){heapinsert(h,t->v);}    //verificar se esta ou esteve na fila
                
                if (P < h->wt[w = t->v])
                {
                    h->wt[w] = P;
                    h->st[w] = v;
                    fixup(h,w);
                }
                
            }
        }
    }
    return;
}