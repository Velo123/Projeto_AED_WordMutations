#ifndef scan
#define scan

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct dicio sdict;


sdict *scandict(char *argv[]);
char *retwadd(sdict *dict,int tam,int pos);
void sdprintf(sdict *dict);
void sdfree(sdict *dict);
int getwpos(sdict *dict,char *pal);


#endif