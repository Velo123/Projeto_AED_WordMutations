#include "Main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }

    sdict *dict;

    dict=scandict(argv);
    //sdprintf(dict);
    sdfree(dict);
    
    return 0;
}