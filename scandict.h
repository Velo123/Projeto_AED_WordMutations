#ifndef scan
#define scan

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct dicio sdict;


sdict *scandict(char *argv[]);

void pt(sdict *dict);
void freedict(sdict *dict);

#endif