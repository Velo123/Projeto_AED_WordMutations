#include "scandict.h"

struct dicio{
    char ***dict;
    int *tam;
    int max_size;
};


sdict *scandict(char *argv[]){
    
    sdict *srdict=(sdict*)malloc(sizeof(sdict));
    if(srdict==NULL){
        printf("Impossivel alocar\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *ptr = fopen(argv[1],"r");
    if(ptr==NULL){
        printf("Nao foi possivel abrir o ficheiro");
        exit(EXIT_FAILURE);
    }
    char temp;
    char strlida[40];
    int cnt=0, size=0;
    int npals[40];
    int max_size=0;
    for (int i = 0; i < 40; i++)
    {
        npals[i]=0;
    }
    while((temp=fgetc(ptr))!=EOF){
        if(temp>='a' && temp<='z'){ //ler letras validas
            strlida[cnt]=temp;  //colocar no vetor
            cnt++;
        }
        else if((temp==' ' || temp=='\t' || temp=='\n') && cnt!=0){ //ler fim de palavra
            strlida[cnt]='\0';  //declarar fim de string no vetor
            size = strlen(strlida);
            if (size>max_size)
            {
                max_size=size;
            }
            npals[size-2]++;
            cnt=0;
        }else if(((temp<'a' && temp>'z') || (temp==' ' || temp=='\t' || temp=='\n')) && cnt<=1){    //descartar carateres nao validos
            cnt=0; 
        }else{
            cnt=0;
        }
    }
    fseek(ptr,0,SEEK_SET);
    srdict->max_size=max_size;
    srdict->tam=(int*)malloc((max_size-1)*sizeof(int));
    
    if(srdict->tam==NULL){
        printf("Impossivel alocar\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < max_size-1; i++)
    {
        srdict->tam[i]=npals[i];
    }
    
    srdict->dict=(char***)malloc((max_size-1)*sizeof(char**));

    if(srdict->dict==NULL){
        printf("Impossivel alocar\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<max_size-1;i++){
        srdict->dict[i]= (char**)malloc((npals[i])*sizeof(char*));   //alocacao do nr de palavras
        if (srdict->dict[i]==NULL)
        {
            exit(EXIT_FAILURE);
            printf("Impossivel alocar para o tamanho %d",i+2);
        }
    }
    while((temp=fgetc(ptr))!=EOF){
        if(temp>='a' && temp<='z'){ //ler letras validas
            strlida[cnt]=temp;  //colocar no vetor
            cnt++;
        }
        else if((temp==' ' || temp=='\t' || temp=='\n') && cnt>1){ //ler fim de palavra
            strlida[cnt]='\0';  //declarar fim de string no vetor
            size = strlen(strlida);
            cnt=0;
            npals[size-2]--;
            srdict->dict[size-2][npals[size-2]]=(char*)malloc((strlen(strlida)+1)*sizeof(char));
            if (srdict->dict[size-2][npals[size-2]]==NULL)
            {
                exit(EXIT_FAILURE);
                printf("Impossivel alocar para o tamanho size=%d e npals=%d",size-2,npals[size-2]);
            }
            strcpy(srdict->dict[size-2][npals[size-2]],strlida);
        }else if(((temp<'a' && temp>'z') || (temp==' ' || temp=='\t' || temp=='\n')) && cnt<=1){    //descartar carateres nao validos
            cnt=0; 
        }else{
            cnt=0;
        }
    }
    /*for (int i = 0; i < max_size-1; i++)
    {
        for (int j = 0; dict[i][j]!="#EOL"; j++)
        {
            printf("s=%d c=%d v=%s\t",i,j,dict[i][j]);
        }
    }*/
    fclose(ptr);
    return srdict;
}

void freedict(sdict *dict){
    int aux=0;
    for (int i = 0; i < dict->max_size-1; i++)
    {
        for (int j = 0; j < dict->tam[i]; j++)
        {
            free(dict->dict[i][j]);
        }
        free(dict->dict[i]);
    }
    free(dict->dict);
    free(dict->tam);
    free(dict);
}

void pt(sdict *dict){
    for (int i = 0; i < dict->max_size-1; i++)
    {
        for (int j = 0; j < dict->tam[i]; j++)
        {
            printf("%s\n",dict->dict[i][j]);
        }
    }
}