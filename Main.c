#include "WordMutations.h"
void scandict(char *argv[]);


int main(int argc, char *argv[]){

    if (argc!=3)
    {
        printf("Programa invocado incorretamente");
        return -1;
    }
    scandict(argv);
    
    return 0;
}