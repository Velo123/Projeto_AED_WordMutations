#include "main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        exit(EXIT_FAILURE);
    }
    sdict *dict = scandict(argv);;
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
    
    int t1=0, t2=0;

    prob p;
    while (!feof(ifp))
    {
        rprob(ifp,&p);
        if (p.mod==1)
        {
            if((t1=getwpos(dict,p.pal1))==-1){
                fprintf(ofp,"%s %s %d\n\n",p.pal1,p.pal2,p.mod);
            }
            else{   
                fprintf(ofp,"%s %d\n\n",p.pal1,getsizetotal(dict,strlen(p.pal1)-2));
            }
        }
        else if(p.mod==2)
        {
            if(((t1=getwpos(dict,p.pal1))==-1) || ((t2=getwpos(dict,p.pal2))==-1)){
                fprintf(ofp,"%s %s %d\n\n",p.pal1,p.pal2,p.mod);
            }
            else{   
                fprintf(ofp,"%s %d\n%s %d\n\n",p.pal1,t1,p.pal2,t2);
            }
        }
        else
        {
            fprintf(ofp,"%s %s %d\n\n",p.pal1,p.pal2,p.mod);
        }
    }
    fclose(ifp);
    fclose(ofp);
    sdfree(dict);
    return 0;
}