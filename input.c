#include "input.h"

typedef struct prob{
     int mod;
    char *pal1[100];
    char *pal2[100];
    };


void inputproblemas(char *argv[]){

FILE * probptr;

probptr = fopen(argv[2],"r");
    if(probptr==NULL){
        printf("Nao foi possivel abrir o ficheiro");
        exit(EXIT_FAILURE);
    }
 
     prob *p;

    
    fscanf(probptr, "%s %s %d \n", p->pal1, p->pal2, p->mod);
    printf("%s %s %d \n", p->pal1,p->pal2,p->mod); 
}

    

    

