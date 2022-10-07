#include "Main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        printf("Programa invocado incorretamente");
        exit(EXIT_FAILURE);
    }

    sdict *dict = scandict(argv);;
    FILE *ifp = openinputfile(argv);
    FILE *ofp = openfile(argv);
    prob *p;
    
    while (!feof(ifp))
    {
        p=rprob(ifp);
        if (getprobtype(p)==1)
        {
            fprintf(ofp,"%s %d\n",getprobword1(p),getsizetotal(dict,strlen(getprobword1(p))-2));
        }
        else if (getprobtype(p)==2)
        {   
            fprintf(ofp,"%s %d\n%s %d\n\n",getprobword1(p),getwpos(dict,getprobword1(p)),getprobword2(p),getwpos(dict,getprobword2(p)));
        }
        freeprob(p);
    }
    fclose(ifp);
    fclose(ofp);
    sdfree(dict);
    
    return 0;
}