#include "Main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }

    sdict *dict;
    FILE *ifp = openinputfile(argv);
    prob *p;
    

    dict=scandict(argv);
    sdprintf(dict);

    //FILE *ofp = openfile(argv);
    while (!feof(ifp))
    {
        p=rprob(ifp);


        if (getprobtype(p)==1)
        {
            
        }
        else if (getprobtype(p)==2)
        {
            
        }
        
        

        
        
        freeprob(p);
    }
    sdfree(dict);
    fclose(ifp);
    return 0;
}


void searchandprint(prob* p){
    
}