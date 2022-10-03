#include "Main.h"

int main(int argc, char *argv[]){
    int max_size=0, min_size=0;
    if (argc!=3) 
    {
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }else if(strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }

    sdict *dict;

    dict=scandict(argv);

    freedict(dict);
    
    return 0;
}