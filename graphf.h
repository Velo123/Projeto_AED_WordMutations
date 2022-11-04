
#ifndef graphf
#define graphf

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"heap1.h"



typedef struct edges edge;

typedef struct _graph
{
    edge** g;
    int nv;
    
}graph;

graph* creategraph(int graphsize);
void addedge(edge** gp,int pos,int w,int v);
edge* getgraphhead(edge** g,int pos);
int getv(edge* g);
int getw(edge* g);
edge* getgraphnext(edge* e);
void freegraph(graph* gi);
void dijkstra(graph *g, int s,heapnode* fn,int max,int d);



#endif