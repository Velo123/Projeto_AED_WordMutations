#ifndef input
#define input

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct problem prob;
prob *rprob(FILE *probptr);
FILE *openinputfile(char *argv[]);
void printprob(prob* p);
void freeprob(prob* p);
char* getprobword1(prob* p);
char* getprobword2(prob* p);
int getprobtype(prob* p);

#endif


