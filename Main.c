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


        /*for (int k = 0; k < gi->nv; k++)
        {
            edge* aux=getgraphhead(gi->g,k);
            printf("V%s= ",retwadd(dict,i+2,k));

            while (aux!=NULL)
            {
                printf(" %s:%d ",retwadd(dict,i+2,getv(aux)),getw(aux));              
                aux=getgraphnext(aux);
            }
            printf("\n");
        }*/


        heap* h=iniheap(gi->nv);
        for (int k = 0; k < d->totpsize[i]; k++)
        {
            dijkstra(gi,d->file[d->nrpsize[i][k]].pal1,h);
            int aux=d->file[d->nrpsize[i][k]].pal2;
            //printf("%d\n",aux);
            /*for (int l = 0; l < gi->nv; l++)
            {
                printf("%d\t",st[l]);
            }*/
            //printf("\n");
            
            if(h->st[aux]==-1){
                d->file[d->nrpsize[i][k]].sols=NULL;
            }
            else
            {
                d->file[d->nrpsize[i][k]].p=h->wt[aux];
                sol* temp1;
                d->file[d->nrpsize[i][k]].sols=(sol*)malloc(sizeof(sol));
                d->file[d->nrpsize[i][k]].sols->w=h->st[aux];
                d->file[d->nrpsize[i][k]].sols->next=NULL;
                aux=h->st[aux];
                while (h->st[h->st[aux]]!=-1)
                {
                    //printf("%s\n",retwadd(dict,i+2,d->file[d->nrpsize[i][k]].sols->w));
                    temp1=(sol*)malloc(sizeof(sol));
                    temp1->w=h->st[aux];
                    temp1->next=d->file[d->nrpsize[i][k]].sols;
                    d->file[d->nrpsize[i][k]].sols=temp1;
                    aux=h->st[aux];   
                }
                //printf("%s %d\n",retwadd(dict,i+2,d->file[d->nrpsize[i][k]].sols->w),d->file[d->nrpsize[i][k]].p);
            }
        }
        //heapfree(h);
        //freegraph(gi);
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
    return (dif*dif);
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
                //return NULL;
            }       
            d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2;
            d->file[d->nrpsize[s][i]].p=0;
            d->file[d->nrpsize[s][i]].sols->next=NULL;
            necgrafo++;
            continue;
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