#ifndef scan
#define scan

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"algorithms.h"

typedef struct dicio sdict;


sdict *scandict(char *argv[]);
char *retwadd(sdict *dict,int tam,int pos);
void sdprintf(sdict *dict);
void sdfree(sdict *dict);
int getwpos(sdict *dict,char *pal);
int getsizetotal(sdict *dict,int size);
void ordenardict(sdict* dict);
char* getword(sdict* dict,int s,int p);
int getmaxsize(sdict* dict);

#endif