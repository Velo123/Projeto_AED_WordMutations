#ifndef input
#define input

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct problem{
    char pal1[101];
    char pal2[101];
    int mod;
}prob;


void rprob(FILE *probptr,prob *p);
void printprob(prob* p);
void freeprob(prob* p);
char* getprobword1(prob* p);
char* getprobword2(prob* p);
int getprobtype(prob* p);

#endif


