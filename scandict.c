#include "scandict.h"

char ***scandict(char *argv[],int* max_size, int* min_size){
    FILE *ptr = fopen(argv[1],"r");
    if(ptr==NULL){
        printf("Nao foi possivel abrir o ficheiro");
        exit(EXIT_FAILURE);
    }
    char temp;
    char strlida[40];
    int cnt=0, size=0;
    int npals[40];
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
            if (size>*max_size)
            {
                *max_size=size;
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
    char ***dict=(char***)malloc((*max_size-1)*sizeof(char**));
    if(dict==NULL){
        printf("Impossivel alocar\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<*max_size-1;i++){
        dict[i]= (char**)malloc((npals[i]+1)*sizeof(char*));   //alocacao do nr de palavras
        if (dict[i]==NULL)
        {
            exit(EXIT_FAILURE);
            printf("Impossivel alocar para o tamanho %d",i+2);
        }
        dict[i][npals[i]]=(char*)malloc(5*sizeof(char));
        dict[i][npals[i]] = "#EOL";
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
            dict[size-2][npals[size-2]]=(char*)malloc((strlen(strlida)+1)*sizeof(char));
            if (dict[size-2][npals[size-2]]==NULL)
            {
                exit(EXIT_FAILURE);
                printf("Impossivel alocar para o tamanho size=%d e npals=%d",size-2,npals[size-2]);
            }
            strcpy(dict[size-2][npals[size-2]],strlida);
        }else if(((temp<'a' && temp>'z') || (temp==' ' || temp=='\t' || temp=='\n')) && cnt<=1){    //descartar carateres nao validos
            cnt=0; 
        }else{
            cnt=0;
        }
    }
    /*for (int i = 0; i < *max_size-1; i++)
    {
        for (int j = 0; dict[i][j]!="#EOL"; j++)
        {
            printf("s=%d c=%d v=%s\t",i,j,dict[i][j]);
        }
    }*/
    fclose(ptr);
    return dict;
}

void freedict(char*** dict,int* max_size,int* min_size){
    int aux=0;
    for (int i = 0; i < *max_size-1; i++)
    {
        for (int j = 0; dict[i][j]!="#EOL"; j++,aux++)
        {
            free(dict[i][j]);
        }
        //free(dict[i][aux]);
        free(dict[i]);
    }
    free(dict);
}