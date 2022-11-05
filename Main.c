#include "main.h"
#define maxWT 1000000

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
        if (sanity_check(d,i,dict)==0)
        {
            continue;
        }
        graph* gi=creategraph(getsizetotal(dict,i));
        for (int cgf = 0; cgf < gi->nv; cgf++)
        {
            char* w1=retwadd(dict,i+2,cgf);
            for (int cgd = cgf; cgd < gi->nv; cgd++)
            {
                char* w2=retwadd(dict,i+2,cgd);
                int difs=verifdif(w1,w2,d->maxmut[i]);
                if (difs>0)
                {
                    addedge(gi->g,cgf,difs,cgd);
                    addedge(gi->g,cgd,difs,cgf);
                }
            }
        }
        heapnode* fn=(heapnode*)malloc(gi->nv*sizeof(heapnode));
        if(fn==NULL){
            freedata(d);
            fclose(ifp);
            fclose(ofp);
            sdfree(dict);
            freegraph(gi);
            exit(EXIT_FAILURE);    
        }
        int r;
        for (int k = 0; k < d->totpsize[i]; k++)
        {
            if (d->file[d->nrpsize[i][k]].pal1!=-1 && d->file[d->nrpsize[i][k]].sols!=NULL)
            {
                continue;
            }
            
            int aux=d->file[d->nrpsize[i][k]].pal2;
            for (int l = 0; l < gi->nv; l++)
            {
                fn[l].from=-1;
                fn[l].visited=0;
                fn[l].w=maxWT;
                fn[l].v=l;
            }
            r = dijkstra(gi,d->file[d->nrpsize[i][k]].pal1,fn,d->maxmut[i],d->file[d->nrpsize[i][k]].pal2);
            if (r==-1)
            {
                free(fn);
                freedata(d);
                fclose(ifp);
                fclose(ofp);
                sdfree(dict);
                freegraph(gi);
                exit(EXIT_FAILURE); 
            }
            else if(r==0){
                d->file[d->nrpsize[i][k]].p=-1;
                d->file[d->nrpsize[i][k]].sols=NULL;
            }
            else if(r==1)
            {
                d->file[d->nrpsize[i][k]].p=fn[aux].w;
                sol* temp1;
                d->file[d->nrpsize[i][k]].sols=(sol*)malloc(sizeof(sol));
                if (d->file[d->nrpsize[i][k]].sols==NULL)
                {
                    free(fn);
                    freegraph(gi);
                    freedata(d);
                    fclose(ifp);
                    fclose(ofp);
                    sdfree(dict);
                    exit(EXIT_FAILURE);
                }
                
                d->file[d->nrpsize[i][k]].sols->w = d->file[d->nrpsize[i][k]].pal2;
                d->file[d->nrpsize[i][k]].sols->next=NULL;
                while (fn[fn[aux].from].from!=-1)
                {
                    temp1=(sol*)malloc(sizeof(sol));
                    if (temp1==NULL)
                    {
                        sol* temp2;
                        temp1=d->file[d->nrpsize[i][k]].sols;
                        while (temp1->next!=NULL)
                        {
                            temp2=temp1;
                            temp1=temp1->next;
                            free(temp2);
                        }
                        free(d->file[d->nrpsize[i][k]].sols);
                        free(fn);
                        freegraph(gi);
                        freedata(d);
                        fclose(ifp);
                        fclose(ofp);
                        sdfree(dict);
                        exit(EXIT_FAILURE);
                    }
                    temp1->w=fn[aux].from;
                    temp1->next=d->file[d->nrpsize[i][k]].sols;
                    d->file[d->nrpsize[i][k]].sols=temp1;
                    aux=fn[aux].from;   
                }
            }
        }
        free(fn);
        freegraph(gi);
    }
    printprob(d,dict,ofp);
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
    return (dif);
}

int sanity_check(probdata* d, int s,sdict* dict){

    int necgrafo=0;
    for (int i = 0; i < d->totpsize[s]; i++)
    {
        d->file[d->nrpsize[s][i]].p=0;
        if ((d->file[d->nrpsize[s][i]].mod==0 && d->file[d->nrpsize[s][i]].pal1==d->file[d->nrpsize[s][i]].pal2) || (d->file[d->nrpsize[s][i]].pal1==d->file[d->nrpsize[s][i]].pal2))
        {
            
            /*colocar como solucao o proprio problema*/
            d->file[d->nrpsize[s][i]].sols=(sol*)malloc(sizeof(sol));
            if(d->file[d->nrpsize[s][i]].sols==NULL){
                exit(EXIT_FAILURE);
            }       
            d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2;
            d->file[d->nrpsize[s][i]].p=0;
            d->file[d->nrpsize[s][i]].sols->next=NULL;
            necgrafo++;
            continue;
        }
        else if((d->file[d->nrpsize[s][i]].mod==0 && d->file[d->nrpsize[s][i]].pal1!=d->file[d->nrpsize[s][i]].pal2)){
            d->file[d->nrpsize[s][i]].p=-1;
            d->file[d->nrpsize[s][i]].sols=NULL;
            necgrafo++;
        }
        else
        {
            int difs=0;
            char* w1=retwadd(dict,s+2,d->file[d->nrpsize[s][i]].pal1);
            char* w2=retwadd(dict,s+2,d->file[d->nrpsize[s][i]].pal2);
            for (int j = 0; j < s+2; j++)
            {
                if (w1[j]!=w2[j])
                {
                    difs++;
                }
            }
            if(difs==1){
                necgrafo++;
                /*colocar como solucao o proprio problema e custo 1*/
                d->file[d->nrpsize[s][i]].sols=(sol*)malloc(sizeof(sol));
                d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2;
                d->file[d->nrpsize[s][i]].p=1;
                d->file[d->nrpsize[s][i]].sols->next=NULL;
            }
        
        }
    }
    if(necgrafo==d->totpsize[s]){
        return 0;
    }
    return 1;
}