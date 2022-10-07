#include  "output.h"

FILE *openfile(char *argv[]){
    char ext[]=".stats";
    char* fout = argv[2];
    char* temp = strstr(fout,".pals");
    
    memmove(temp,ext,7);

    FILE *fp=fopen(fout,"w+");
    if(fp==NULL){
        printf("Nao foi possivel abrir o ficheiro de saida");
        exit(EXIT_FAILURE);
    }
    
    return fp;
}