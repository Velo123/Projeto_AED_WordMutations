#include "Main.h"

int main(int argc, char *argv[]){

    if (argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL)
    {
        printf("Programa invocado incorretamente");
        return -1;
    }
    scandict(argv);
    
    return 0;
}