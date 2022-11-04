#include "input.h"


probdata* scinput(FILE *probptr,sdict *dict){
    int totalprobs=0;
    char temp1[101];
    char temp2[101];
    int mut=0;
    int maxwsize=0;
    int dif=0;
    int maxmut[101]={0};
    int s1=0,s2=0,fails=0,t1=0,t2=0;
    int totalprobspsize[101]={0};
    while(!feof(probptr)){
        if(fscanf(probptr,"%s %s %d\n",temp1,temp2,&mut)==3){
            totalprobs++;
            if((s1=strlen(temp1))!=(s2=strlen(temp2)) || (t1=getwpos(dict,temp1))==-1 || (t2=getwpos(dict,temp2))==-1 || mut<0){
                fails++;
                totalprobspsize[s1-2]--;
            }
            totalprobspsize[s1-2]++;
            if (s1>maxwsize)
            {
                maxwsize=s1;
            }
            if (s1==s2)
            {
                dif=0;
                for (int i = 0; i < s1; i++)
                {
                    if (temp1[i]!=temp2[i])
                    {
                        dif++;
                    }
                }    
                if(dif>=mut && mut>maxmut[s1-2])
                {
                    maxmut[s1-2]=mut;
                }
                else if(dif<mut && mut>maxmut[s1-2]){
                    maxmut[s1-2]=dif;
                }
            }
        }
    }
    probdata* data=(probdata*)malloc(sizeof(probdata));
    if (data==NULL)
    {
        return NULL;
    }
    data->maxwsize=maxwsize;
    data->totprobs=totalprobs;
    data->totpsize=(int*)calloc(maxwsize-1,sizeof(int));
    if (data->totpsize==NULL)
    {
        free(data);
        return NULL;
    }
    data->maxmut=(int*)calloc(maxwsize-1,sizeof(int));
    if (data->maxmut==NULL)
    {
        free(data->totpsize);
        free(data);
        return NULL;
    }
    for (int i = 0; i < data->maxwsize-1; i++)
    {
        data->totpsize[i]=totalprobspsize[i];
        data->maxmut[i]=maxmut[i];
    }
    data->nrpsize=(int**)calloc(maxwsize-1,sizeof(int*));
    if (data->nrpsize==NULL)
    {
        free(data->maxmut);
        free(data->totpsize);
        free(data);
        return NULL;
    }
    for (int i = 0; i < maxwsize-1; i++)
    {
        data->nrpsize[i]=(int*)calloc(totalprobspsize[i],sizeof(int));
        if (data->nrpsize[i]==NULL)
        {
            free(data->nrpsize);
            free(data->maxmut);
            free(data->totpsize);
            free(data);
            return NULL;
        }    
    }
    data->file=(prob*)malloc(totalprobs*sizeof(prob));
    if (data->file==NULL)
    {
        for (int i = 0; i < maxwsize-1; i++)
        {
            free(data->nrpsize[i]);
        }
        free(data->nrpsize);
        free(data->maxmut);
        free(data->totpsize);
        free(data);
        return NULL;
    }

    if (fails!=0)
    {
        data->fv=(pfail*)malloc(fails*sizeof(pfail));
        if (data->fv==NULL)
        {
            for (int i = 0; i < maxwsize-1; i++)
            {
                free(data->nrpsize[i]);
            }
            free(data->file);
            free(data->nrpsize);
            free(data->maxmut);
            free(data->totpsize);
            free(data);
            return NULL;
        }  
    }
    fseek(probptr,0,SEEK_SET);
    int cntp=0,cntf=0;
    while(!feof(probptr)){
        if(fscanf(probptr,"%s %s %d\n",temp1,temp2,&mut)==3){
            if((s1=strlen(temp1))==(s2=strlen(temp2)) && (t1=getwpos(dict,temp1))!=-1 && (t2=getwpos(dict,temp2))!=-1 && mut>=0){
                data->file[cntp].pal1=t1;
                data->file[cntp].pal2=t2;
                data->file[cntp].mod=mut;
                data->file[cntp].s=s1;
                data->nrpsize[s1-2][--totalprobspsize[s1-2]]=cntp;
                data->file[cntp].sols=NULL;
                cntp++;       
            }else{
                data->file[cntp].pal1=-1;
                data->file[cntp].pal2=-1;
                data->file[cntp].mod=cntf;
                data->file[cntp].s=-1;
                data->file[cntp].sols=NULL;
                data->fv[cntf].pal1=(char*)malloc((s1+1)*sizeof(char));
                if (data->fv[cntf].pal1==NULL)
                {
                    if (fails!=0)
                    {  
                        free(data->fv);
                    }
                    for (int i = 0; i < maxwsize-1; i++)
                    {
                        free(data->nrpsize[i]);
                    }
                    free(data->file);
                    free(data->nrpsize);
                    free(data->maxmut);
                    free(data->totpsize);
                    free(data);
                    return NULL;
                }
                data->fv[cntf].pal2=(char*)malloc((s2+1)*sizeof(char));
                if (data->fv[cntf].pal2==NULL)
                {
                    free(data->fv[cntf].pal1);
                    if (fails!=0)
                    {  
                        free(data->fv);
                    }
                    for (int i = 0; i < maxwsize-1; i++)
                    {
                        free(data->nrpsize[i]);
                    }
                    free(data->file);
                    free(data->nrpsize);
                    free(data->maxmut);
                    free(data->totpsize);
                    free(data);
                    return NULL;
                }
                strcpy(data->fv[cntf].pal1,temp1);
                strcpy(data->fv[cntf].pal2,temp2);
                cntp++;
                cntf++;
            }
        }
    }
    return data;
}

void printprob(probdata* d,sdict* dict,FILE* ofp){
    sol* aux;
    for (int i = 0; i < d->totprobs; i++)
    {   
        if (d->file[i].pal1==-1 || d->file[i].pal2==-1 || d->file[i].mod<0)
        {
            fprintf(ofp,"%s -1\n%s\n",d->fv[d->file[i].mod].pal1,d->fv[d->file[i].mod].pal2);
        }
        else
        {
            fprintf(ofp,"%s %d\n",retwadd(dict,d->file[i].s,d->file[i].pal1),d->file[i].p);
            sol* ftemp;
            aux=d->file[i].sols;
            while (aux!=NULL)
            {
                ftemp=aux;
                fprintf(ofp,"%s\n",retwadd(dict,d->file[i].s,aux->w));
                aux=aux->next;
                free(ftemp);
            }
            fprintf(ofp,"%s\n",retwadd(dict,d->file[i].s,d->file[i].pal2));
        }
        fprintf(ofp,"\n");   
    }
    return;
}

void freedata(probdata* d){
    int aux=0;
    for (int i = 0; i < d->totprobs; i++)
    {
        if (d->file[i].pal1==-1 || d->file[i].pal2==-1)
        {
            free(d->fv[d->file[i].mod].pal1);
            free(d->fv[d->file[i].mod].pal2);
            aux++;
        }
    }
    if (aux!=0)
    {
        free(d->fv);
    }
    free(d->file);  
    for (int i = 0; i < d->maxwsize-1; i++)
    {
        free(d->nrpsize[i]);
    }
    free(d->nrpsize);
    free(d->maxmut);
    free(d->totpsize);
    free(d);
    return;
}