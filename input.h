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
}pfail;

typedef struct problem{
    int pal1;   //index of pal1 in dict
    int pal2;   //index of pal2 in dict
    int mod;    //number of mutations
    int s;  //size of the word
    int p;  //number of the problem
    sol* sols;  //list of solutions
}prob;

typedef struct probdata{
    int** nrpsize;     //index of a problem on file vector
    int* totpsize;  //total number of problems of size i
    int* maxmut;    //max number of mutations of size i
    int maxwsize;   //max word size
    int totprobs;   //total number of problems
    pfail* fv;  //badly defined problems
    prob* file; //problems
}probdata;



probdata* scinput(FILE *probptr,sdict *dict);
void printprob(probdata* d,sdict* dict,FILE* ofp);
void freedata(probdata* d);
void printinputs(sdict*dict,probdata* d);

#endif