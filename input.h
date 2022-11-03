#ifndef input
#define input

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "scandict.h"


typedef struct _sol sol;
typedef struct _sol{
    int w;
    sol* next;
}sol;

typedef struct failproblem{
    char* pal1;
    char* pal2;
    //int mod;
}pfail;

typedef struct problem{
    int pal1;
    int pal2;
    int mod;
    int s;
    int p;
    sol* sols;
}prob;

typedef struct probdata{
    int** nrpsize;
    int* totpsize;
    int* maxmut;
    int maxwsize;
    int totprobs;
    pfail* fv;
    prob* file;
}probdata;



probdata* scinput(FILE *probptr,sdict *dict);
void printprob(probdata* d,sdict* dict,FILE* ofp);
void freedata(probdata* d);

#endif