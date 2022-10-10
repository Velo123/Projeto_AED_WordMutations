#include  "output.h"

FILE *openfile(char *argv[]){
    char *fout=(char*)malloc((strlen(argv[2])+2)*sizeof(char));
    if (fout==NULL)
        return 0;
    strcpy(fout,argv[2]);
    fout[strlen(argv[2])-5]='\0';
    strcat(fout,".stats");
    FILE *fp=fopen(fout,"w");
    free(fout);
        
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