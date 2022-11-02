#include "main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        exit(EXIT_FAILURE);
    }
    sdict *dict = scandict(argv);
    if (dict==NULL)
    {
        exit(EXIT_FAILURE);
    }

    ordenardict(dict);

    FILE *ifp = fopen(argv[2],"r");
    if(ifp==NULL){
        sdfree(dict);
        exit(EXIT_FAILURE);
    }

    FILE *ofp = openfile(argv);
    if(ofp==NULL){
        sdfree(dict);
        fclose(ifp);
        exit(EXIT_FAILURE);
    }

    probdata* d=scinput(ifp,dict);
    for (int i = 0; i < d->maxwsize-1; i++)
    {
        if (d->totpsize[i]==0)
        {
            continue;
        }
        int st=getsizetotal(dict,i);
        edge** g=creategraph(st);
        for (int cgf = 0; cgf < st; cgf++)
        {
            char* w1=retwadd(dict,i+2,cgf);
            for (int cgd = cgf; cgd < st; cgd++)
            {
                char* w2=retwadd(dict,i+2,cgd);
                int difs=verifdif(w1,w2,d->maxmut[i]);
                if (difs>0)
                {
                    addedge(g,cgf,difs,cgd);
                    addedge(g,cgd,difs,cgf);
                }
            }
        }
        /*for (int k = 0; k < st; k++)
        {
            edge* aux=getgraphhead(g,k);
            printf("V%s= ",retwadd(dict,i+2,k));

            while (aux!=NULL)
            {
                printf(" %s:%d ",retwadd(dict,i+2,getv(aux)),getw(aux));
                aux=getgraphnext(aux);
            }
            printf("\n");
        }*/
        freegraph(g,st);
    }
    freedata(d);
    fclose(ifp);
    fclose(ofp);
    sdfree(dict);
    return 0;
}

int verifdif(char* w1, char* w2,int d){
    int dif=0;
    int s=strlen(w1);
    for (int i = 0; i < s; i++)
    {
        if (w1[i]!=w2[i])
        {
            dif++;
            if (dif>d)
            {
                return 0;
            }
            
        }
    }
    return dif;
}