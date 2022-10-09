#include "Main.h"

int main(int argc, char *argv[]){
    if(argc!=3 || strstr(argv[1],".dict")==NULL || strstr(argv[2],".pals")==NULL){
        exit(EXIT_FAILURE);
    }
    sdict *dict = scandict(argv);;
    if (dict==NULL)
    {
        exit(EXIT_FAILURE);
    }

    FILE *ifp = openinputfile(argv);
    FILE *ofp = openfile(argv);
    ordenardict(dict);
    prob p;
    while (!feof(ifp))
    {
        rprob(ifp,&p);
        if (p.mod==1)
        {
            fprintf(ofp,"%s %d\n\n",p.pal1,getsizetotal(dict,strlen(p.pal1)-2));
        }
        else if(p.mod==2)
        {
            fprintf(ofp,"%s %d\n%s %d\n\n",p.pal1,getwpos(dict,p.pal1),p.pal2,getwpos(dict,p.pal2));
        }
        else
        {
            fprintf(ofp,"%s %s %d\n",p.pal1,p.pal2,p.mod);
        }
    }
    fclose(ifp);
    fclose(ofp);
    sdfree(dict);
    
    return 0;
}