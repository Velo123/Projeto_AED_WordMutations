#include  "output.h"

FILE *openfile(char *argv[]){
    char ext[]=".stats";
    char* fout = argv[2];
    char* temp = strstr(fout,".pals");
    
    memmove(temp,ext,7);

    FILE *fp=fopen(fout,"w+");
    
    return fp;
}

void deletef(char* argv[]){
    char ext[]=".stats";
    char* fout = argv[2];
    char* temp = strstr(fout,".pals");
    
    memmove(temp,ext,7);

    remove(fout);

    return;
}