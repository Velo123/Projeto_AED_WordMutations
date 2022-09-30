#include "WordMutations.h"

int main(int argc, char *argv[]){

    if (argc!=3)
    {
        printf("Programa invocado incorretamente");
        return -1;
    }
    printf("%s\n",argv[2]);
    scandict(argv);
    
    return 0;
}