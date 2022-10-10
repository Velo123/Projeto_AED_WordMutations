#include "input.h"

void rprob(FILE *probptr,prob *p){
    char pal1[100],pal2[100];
    if(fscanf(probptr,"%s %s %d\n",pal1,pal2,&p->mod)!=3){
        return;
    }
    strcpy(p->pal1,pal1);
    strcpy(p->pal2,pal2);
    return;
}

void printprob(prob* p){
    printf("%s %s %d\n",p->pal1,p->pal2,p->mod);
    return;
}

void freeprob(prob* p){
    free(p->pal1);
    free(p->pal2);
    free(p);
}

char* getprobword1(prob* p){
    return p->pal1;
}

char* getprobword2(prob* p){
    return p->pal2;
}

int getprobtype(prob* p){
    return p->mod;
}