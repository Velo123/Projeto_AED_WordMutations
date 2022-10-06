#include  "output.h"

struct pout{
    char *pal1;
    char *pal2;
    int vals[2];
};

FILE *openfile(char *argv[]){
    char ext[]=".paths";
    
    char* fout=(char*)malloc((strlen(argv[2])+7)*sizeof(char));
    if(fout==NULL){
        printf("Impossivel alocar\n");
        exit(EXIT_FAILURE);
    }
    fout=argv[2];
    char* temp=strstr(fout,".pals");
    fout=strcat(argv[2],temp);
    
    memmove(temp,ext,7);

    FILE *fp=fopen(fout,"w+");
    return fp;
}

pout *searchword(char* pal1,char* pal2){
    
}