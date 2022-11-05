#include "scandict.h"


/*Data Type: (struct) dicio
 
   Descrição - estrutura com
       1) ponteiro para vetor de palavras
       2) ponteiro para o tamanho de cada palavra
       3) inteiro que guarda o tamanho da maior palavra
 */
 
struct dicio{
    char ***dict;
    int *tam;
    int max_size;
};

sdict *scandict(char *argv[]){
    sdict *srdict=(sdict*)malloc(sizeof(sdict));//alocação mem
    if(srdict==NULL){
        exit(EXIT_FAILURE);
    }
    srdict->max_size=0;  
    FILE *ptr = fopen(argv[1],"r");
    if(ptr==NULL){
        free(srdict);
        exit(EXIT_FAILURE);
    }
    char temp;
    char strlida[101];
    int cnt=0, size=0;
    int npals[101]={0};
    do{                 //até não chegar ao fim do ficheiro
        temp=fgetc(ptr);       //percorre o ficheiro                
        if((temp>='a' && temp<='z') || (temp>='A' && temp<='Z')){ //ler letras validas    
            strlida[cnt]=temp;  //guarda o vetor 
            cnt++;
        }
        else if(cnt>1 && (temp==' ' || temp=='\t' || temp=='\n')){ //ler fim de palavra
            strlida[cnt]='\0';
            cnt=0;
            size=strlen(strlida);
            if (size>=srdict->max_size) //atualiza valor da palavra de maior tamanho
            {
                srdict->max_size=size;
            }
            npals[size-2]++;        //incrementa o número de palavras de um certo tamanho numa variável temporal
        }
        else if(cnt<=1 && ((temp<'a' && temp>'z') || temp==' ' || temp=='\t' || temp=='\n')){    //descartar carateres nao validos      
            cnt=0; 
        }
    }while(!feof(ptr));

    if (srdict->max_size==0)   
    {
        free(srdict);
        fclose(ptr);
        return NULL;
    }
    fseek(ptr,0,SEEK_SET);
    srdict->tam=(int*)calloc(srdict->max_size-1,sizeof(int));   //alocação de memória para guardar o número de palavras de um certo tamanho 
    if(srdict->tam==NULL){
        free(srdict);
        fclose(ptr);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < srdict->max_size-1; i++)
    {
        srdict->tam[i]=npals[i];  //guardar o numero de palavras de cada tamanho no vetor da estrutura 
    }
    srdict->dict=(char***)malloc((srdict->max_size-1)*sizeof(char**));//alocação de memória para o vetor de tamanho de palavras
    if(srdict->dict==NULL){
        free(srdict->tam);
        free(srdict);
        fclose(ptr);
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<srdict->max_size-1;i++){
        srdict->dict[i]= (char**)malloc((npals[i])*sizeof(char*));   //alocação de memória para o vetor de palavras de tamanho [i]
        if (srdict->dict[i]==NULL)
        {
            free(srdict->dict);
            free(srdict->tam);
            free(srdict);
            fclose(ptr);
            exit(EXIT_FAILURE);
        }
    }
    do{
        temp=fgetc(ptr);
        if((temp>='a' && temp<='z') || (temp>='A' && temp<='Z')){ //ler letras validas
            strlida[cnt]=temp;  //colocar no vetor
            cnt++;
        }
        else if(cnt>1 && (temp==' ' || temp=='\t' || temp=='\n')){ //ler fim de palavra
            strlida[cnt]='\0';  //declarar fim de string no vetor
            size = strlen(strlida);
            cnt=0;
            npals[size-2]--;
            srdict->dict[size-2][npals[size-2]]=(char*)malloc((strlen(strlida)+1)*sizeof(char));  //Alocação de memória para os caracteres 
            if (srdict->dict[size-2][npals[size-2]]==NULL)
            {
                for (int i = 0; i < srdict->max_size-1; i++)
                {
                    free(srdict->dict[i]);
                }
                free(srdict->dict);
                free(srdict->tam);
                free(srdict);
                fclose(ptr);
                exit(EXIT_FAILURE);
            }
            strcpy(srdict->dict[size-2][npals[size-2]],strlida);
        }
        else if(cnt<=1 && ((temp<'a' && temp>'z') || temp==' ' || temp=='\t' || temp=='\n')){    //descartar carateres nao validos
            cnt=0; 
        }
    }while(!feof(ptr));
    fclose(ptr);
    return srdict;
}

void sdfree(sdict *dict){
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

/*void sdprintf(sdict *dict){
    for (int i = 0; i < dict->max_size-1; i++)
    {
        for (int j = 0; j < dict->tam[i]; j++)
        {
            printf("%s\n",dict->dict[i][j]);
        }
    }
}*/

char *retwadd(sdict *dict,int tam,int pos){
    return dict->dict[tam-2][pos];
}

int getwpos(sdict *dict,char *pal){
    int size=strlen(pal);
    if (size<2 || size>dict->max_size)
    {
        return -1;
    }
    int l=0;
    int r=dict->tam[size-2]-1;
    while (l<=r)   
    {
        int m=(l+r)/2;
        if (strcmp(dict->dict[size-2][m],pal)>0)
        {
            r=m-1;
        }
        else if (strcmp(dict->dict[size-2][m],pal)<0)
        {
            l=m+1;
        }
        else
        {
            return m;
        }
    }
    return -1;
}


int getsizetotal(sdict *dict,int size){
    if (size>=dict->max_size-1)
    {
        return -1;
    }
    return dict->tam[size];
}

void ordenardict(sdict* dict){
    for (int i = 0; i < dict->max_size-1; i++)
    {
        quicksort(dict->dict[i],0,dict->tam[i]-1);
    }
}

char* getword(sdict* dict,int s,int p){
    if (s>=dict->max_size-1 || p>=dict->tam[s])
    {
        return NULL;
    }
    return dict->dict[s][p];
}

int getmaxsize(sdict* dict){
    return dict->max_size;
}