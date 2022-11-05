#include"graphf.h"
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

int dijkstra(graph *g, int s,heapnode* fn,int max,int d)
{
    int v, w; 
    edge* t;

    heap* h=iniheap(g->nv);
    if (h==NULL)
    {
        return -1;
    }
    
    heapnode* temp;

    fn[s].w=0;
    heapinsert(h,&fn[s]);
    int c;
    while (h->n_elements!=0)
    {
        temp=pop(h);
        
        if (temp->w != maxWT)
        {
            v=temp->v;
            c=temp->w;
            for (t = g->g[v]; t != NULL; t = t->next)
            { 
                if (fn[t->v].visited==1 || t->w>max){continue;}
                if (fn[t->v].w==maxWT)
                {
                    fn[t->v].w=(t->w)*(t->w)+c;
                    fn[t->v].from=v;
                    heapinsert(h,&fn[t->v]);
                }
                
                else if (fn[t->v].w > (t->w)*(t->w)+c)
                {
                    fn[t->v].w=(t->w)*(t->w)+c;
                    fn[t->v].from=v;
                    fixup(h,t->v);
                }
            }
            temp->visited=1;
            if (v==d)
            {
                ffreefila(h);
                return 1;
            }
        }
    }
    ffreefila(h);
    return 0;
}