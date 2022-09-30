#include "WordMutations.h"

void scandict(char *argv[]){
    //FILE *ptr = fopen(argv[1],"r");
    
    printf("%s\n",argv[1]);
    
    
    /*char str[100];
    int temp;
    int npalavras[size-1];
    for(int i=0;i<size-1;i++){
        npalavras[i]=0;
    }
    char strlida[100];
    char *strptr;
    for(int k=0;k<2;k++){               //Percorrer o ficheiro 2 vezes. A primeira para saber quanta memoria alocar e a sa para alocar a memoria e guardar a string do dicionario
        if(k==0){
            while(fgets(strlida,100,ptr)!=NULL){    //selecao de ate onde as palavras podem ir
                if(strstr(strlida," ")!=NULL){
                    strptr = strtok (strlida, " ");
                }
                if(strstr(strlida,"/")!=NULL){
                    strptr = strtok (strlida, "/");
                }
                if(strstr(strlida,"\t")!=NULL){
                    strptr = strtok (strlida, "\t");
                }
                if(strstr(strlida,"\n")!=NULL){
                    strptr = strtok (strlida, "\n");
                }
                strcpy(str,strptr);
                temp = strlen(str);
                if(temp>=2 && temp<=size){    //saber se a palavra tem mais de duas letras e menos do que o tamanho do tabuleiro
                    int aux=0;

                    for(int j=0;j<temp;j++){                //saber se a palavra tem ou nao acentos.
                        if(str[j]<'a' || str[j]>'z'){
                            aux++;
                        }
                    }
                    if(aux==0){
                        npalavras[temp-2]++;
                    }
                }
            }
            for(int p=0;p<size-1;p++){
                npalavras2[p]=npalavras[p];
            }
        }
        else if(k==1){
            fseek(ptr,0,SEEK_SET);
            for(int l=0;l<size-1;l++){
                dict[l]= (char**)malloc(npalavras2[l]*sizeof(char*));   //alocacao do nr de palavras
            }
            while(fgets(strlida,100,ptr)!=NULL){        //saber se a palavra tem ou nao acentos.
                if(strstr(strlida," ")!=NULL){
                    strptr = strtok (strlida, " ");
                }
                if(strstr(strlida,"/")!=NULL){
                    strptr = strtok (strlida, "/");
                }
                if(strstr(strlida,"\t")!=NULL){
                    strptr = strtok (strlida, "\t");
                }
                if(strstr(strlida,"\n")!=NULL){
                    strptr = strtok (strlida, "\n");
                }
                strcpy(str,strptr);
                temp = strlen(str);
                if(temp>=2 && temp<=size){
                    int aux=0;
                    for(int j=0;j<temp;j++){            //saber se a palavra tem ou nao acentos.
                        if(str[j]<'a' || str[j]>'z'){
                            aux++;
                        }
                    }
                    if(aux==0){         //alocacao do espaco necessario para cada string
                        npalavras[temp-2]--;
                        dict[temp-2][npalavras[temp-2]]= (char*)malloc((strlen(str)+1)*sizeof(char));
                        strcpy(dict[temp-2][npalavras[temp-2]],str);
                    }
                }
            }
        }
    }*/
    //fclose(ptr);
}