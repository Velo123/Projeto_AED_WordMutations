#ifndef graphf
#define graphf

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define item void*

/*typedef struct _graphf
{
    edge** gp;
    int gs;    
}graph;*/


typedef struct edges edge;

edge** creategraph(int graphsize);
void addedge(edge** gp,int pos,int w,int v);
void freegraph(edge** g,int graphsize);
edge* getgraphhead(edge** g,int pos);
int getv(edge* g);
int getw(edge* g);
edge* getgraphnext(edge* e);

#endif