#include"graphf.h"

typedef struct edges
{
    int w;
    int v;
    edge* next;
}edges;



//grafo em tabela de listas
edge** creategraph(int graphsize){
    //printf("GRAPHSIZE: %d",graphsize);
    edge** gp=(edge**)calloc(graphsize,sizeof(edge*));
    return gp;
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
void freegraph(edge** g,int graphsize){
    edge* temp1;
    for (int i = 0; i < graphsize; i++)
    {
        while(g[i]!=NULL){
            temp1=g[i];
            g[i]=g[i]->next;
            free(temp1);
        }
    }
    free(g);
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