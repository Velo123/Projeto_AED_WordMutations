#include "input.h"

struct problem{
    char *pal1;
    char *pal2;
    int mod;
};  

FILE *openinputfile(char *argv[]){

    FILE *probptr = fopen(argv[2],"r");
    if(probptr==NULL){
        printf("Nao foi possivel abrir o ficheiro");
        exit(EXIT_FAILURE);
    }

    return probptr;
}

prob *rprob(FILE *probptr){
    char pal1[100],pal2[100];
    prob *p=(prob*)malloc(sizeof(prob));
    if(fscanf(probptr,"%s %s %d\n",pal1,pal2,&p->mod)!=3){
        printf("Falha ao ler problema");
    }
    p->pal1=(char*)malloc((strlen(pal1)+1)*sizeof(char));
    p->pal2=(char*)malloc((strlen(pal2)+1)*sizeof(char));
    strcpy(p->pal1,pal1);
    strcpy(p->pal2,pal2);
    return p;
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