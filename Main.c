#include "Main.h"

int main(int argc, char *argv[]){
    char ***dict;
    int max_size=0, min_size=0;
    if (argc!=3) 
    {
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }else if(strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }

    dict=scandict(argv,&max_size,&min_size);

    printf("Entrar em frees\n");

    freedict(dict,&max_size,&min_size);

    printf("Concluido\n");
    
    return 0;
}