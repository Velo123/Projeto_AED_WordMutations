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
        if (d->totpsize[i]==0) //verificar se há problemas de tamanho i+2
        {
            continue;
        }
        if (sanity_check(d,i,dict)==0)  //verificar se vale a pena criar grafo
        {
            continue;
        }
        else if (sanity_check(d,i,dict)==-1)  //caso nao seja possivel alocar memoria para solucoes
        {
            freedata(d);
            fclose(ifp);
            fclose(ofp);
            sdfree(dict);
            exit(EXIT_FAILURE);
        }
        //criar grafo e adicionar arestas
        graph* gi=creategraph(getsizetotal(dict,i));   //criar grafo
        for (int cgf = 0; cgf < gi->nv; cgf++)  //adicionar arestas
        {
            char* w1=retwadd(dict,i+2,cgf); //retornar palavra de indice cgf de tamanho i+2
            for (int cgd = cgf; cgd < gi->nv; cgd++)
            {
                char* w2=retwadd(dict,i+2,cgd);
                int difs=verifdif(w1,w2,d->maxmut[i]);  //se difs>0, entao w1 e w2 diferem em difs letras
                if (difs>0)
                {
                    addedge(gi->g,cgf,difs,cgd);    //adicionar aresta de cgf para cgd
                    addedge(gi->g,cgd,difs,cgf);    //adicionar aresta de cgd para cgf
                }
            }
        }
        //criar fakenodes
        heapnode* fn=(heapnode*)malloc(gi->nv*sizeof(heapnode));    //nos fakenodes fica guardado o caminho mais curto de cada vertice para o vertice de origem
        if(fn==NULL){   //caso nao seja possivel alocar memoria para fakenodes - sair do programa
            freedata(d);
            fclose(ifp);
            fclose(ofp);
            sdfree(dict);
            freegraph(gi);
            exit(EXIT_FAILURE);    
        }
        int r;
        for (int k = 0; k < d->totpsize[i]; k++)    //para cada problema de tamanho k+2
        {
            
            if (d->file[d->nrpsize[i][k]].pal1!=-1 && d->file[d->nrpsize[i][k]].sols!=NULL) //verificar se o problema ja foi resolvido em sanity check
            {
                continue;
            }
            //caso o problema nao tenha sido resolvido em sanity check:
            int aux=d->file[d->nrpsize[i][k]].pal2; //guardar palavra de destino em variavel auxiliar
            for (int l = 0; l < gi->nv; l++)    //inicializar fakenodes
            {
                fn[l].from=-1;  //vertice de origem
                fn[l].visited=0;    //vertice nao visitado
                fn[l].w=maxWT;  //peso infinito para todos os vertices pq ainda nenhum foi visitado
                fn[l].v=l;  //vertice atual
            }
            r = dijkstra(gi,d->file[d->nrpsize[i][k]].pal1,fn,d->maxmut[i],d->file[d->nrpsize[i][k]].pal2); //executar dijkstra - r serve para saber se o problema tem solucao
            if (r==-1)  //caso nao seja possivel alocar memoria para solucoes - sair do programa
            {
                free(fn);
                freedata(d);
                fclose(ifp);
                fclose(ofp);
                sdfree(dict);
                freegraph(gi);
                exit(EXIT_FAILURE); 
            }
            else if(r==0){  //problema sem solucao
                d->file[d->nrpsize[i][k]].p=-1; //custo do problema = -1
                d->file[d->nrpsize[i][k]].sols=(sol*)malloc(sizeof(sol));   //criar lista com solucoes
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
                d->file[d->nrpsize[i][k]].sols->w = d->file[d->nrpsize[i][k]].pal2; //guardar palavra de destino na lista de solucoes
                d->file[d->nrpsize[i][k]].sols->next=NULL;  //colocar ultimo elemento da lista a NULL
            }
            else if(r==1) //problema com solucao. criacao de lista com as solucoes em d->file[d->nrpsize[i][k]].sols
            {
                d->file[d->nrpsize[i][k]].p=fn[aux].w;  //guardar custo do problema
                sol* temp1;
                d->file[d->nrpsize[i][k]].sols=(sol*)malloc(sizeof(sol));   //criar lista com solucoes
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
                
                d->file[d->nrpsize[i][k]].sols->w = d->file[d->nrpsize[i][k]].pal2; //guardar palavra de destino na lista de solucoes
                d->file[d->nrpsize[i][k]].sols->next=NULL;  //colocar ultimo elemento da lista a apontar para NULL
                while (fn[fn[aux].from].from!=-1)   //enquanto nao chegar ao vertice de origem
                {
                    temp1=(sol*)malloc(sizeof(sol));    //criar novo elemento da lista de solucoes
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
                    temp1->w=fn[aux].from;  //guardar vertice de onde se veio na lista/ uma palavra pertencente a solucao
                    temp1->next=d->file[d->nrpsize[i][k]].sols; //colocar novo elemento da lista a apontar para o elemento anterior
                    d->file[d->nrpsize[i][k]].sols=temp1;   //colocar novo elemento da lista como primeiro elemento
                    aux=fn[aux].from;   //atualizar vertice de origem
                }
            }
        }
        free(fn); //eliminar fakenodes
        freegraph(gi); //eliminar grafo
    }
    printprob(d,dict,ofp);  //imprimir solucoes
    freedata(d);    //eliminar dados
    fclose(ifp);    //fechar ficheiros
    fclose(ofp);    //fechar ficheiros
    sdfree(dict);   //eliminar dicionario
    return 0;
}

//verificar letras diferentes de 2 palavras. sair quando ultrapassa a mutacao maxima
int verifdif(char* w1, char* w2,int d){
    int dif=0;
    int s=strlen(w1);
    for (int i = 0; i < s; i++)
    {
        if (w1[i]!=w2[i])
        {
            dif++;
            if (dif>d)  //se dif for maior que a mutacao maxima, sair e retornar 0
            {
                return 0;
            }
        }
    }
    return (dif);   //retornar dif caso se possa criar aresta
}

//verificar se vale a pena criar grafo ou correr problemas no grafo de modo a poupar tempo de execucao
int sanity_check(probdata* d, int s,sdict* dict){

    int necgrafo=0;
    for (int i = 0; i < d->totpsize[s]; i++)
    {
        d->file[d->nrpsize[s][i]].p=0;  
        //casos em que as palavras sao iguais ou mutacao=0 e palavras sao iguais
        if ((d->file[d->nrpsize[s][i]].mod==0 && d->file[d->nrpsize[s][i]].pal1==d->file[d->nrpsize[s][i]].pal2) || (d->file[d->nrpsize[s][i]].pal1==d->file[d->nrpsize[s][i]].pal2))
        {
            /*colocar como solucao o proprio problema*/
            d->file[d->nrpsize[s][i]].sols=(sol*)malloc(sizeof(sol));  
            if(d->file[d->nrpsize[s][i]].sols==NULL){
                return -1;
            }       
            d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2;   //colocar como solucao o proprio problema
            d->file[d->nrpsize[s][i]].p=0;  //colocar custo como 0
            d->file[d->nrpsize[s][i]].sols->next=NULL;  //colocar como proximo elemento da lista a solucao o proprio problema
            necgrafo++; //incrementar o numero de problemas que nao precisam de grafo
            continue;
        }
        //casos em que mutacao=0 e palavras sao diferentes
        else if((d->file[d->nrpsize[s][i]].mod==0 && d->file[d->nrpsize[s][i]].pal1!=d->file[d->nrpsize[s][i]].pal2)){
            d->file[d->nrpsize[s][i]].p=-1; //colocar custo como -1
            d->file[d->nrpsize[s][i]].sols=(sol*)malloc(sizeof(sol)); 
            if(d->file[d->nrpsize[s][i]].sols==NULL){
                return -1;
            } 
            d->file[d->nrpsize[s][i]].sols->next=NULL;      
            d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2;   //colocar como output o proprio problema
            necgrafo++; //incrementar o numero de problemas que nao precisam de grafo
        }
        else //casos em que as palavras diferem apenas numa letra 
        {
            int difs=0;
            char* w1=retwadd(dict,s+2,d->file[d->nrpsize[s][i]].pal1);
            char* w2=retwadd(dict,s+2,d->file[d->nrpsize[s][i]].pal2);
            for (int j = 0; j < s+2; j++)   //verificar quantas letras sao diferentes
            {
                if (w1[j]!=w2[j])
                {
                    difs++;
                }
            }
            if(difs==1){        //se a diferenca for 1, sabemos a solucao
                necgrafo++; //incrementar o numero de problemas que nao precisam de grafo
                /*colocar como solucao o proprio problema e custo 1*/
                d->file[d->nrpsize[s][i]].sols=(sol*)malloc(sizeof(sol));
                if(d->file[d->nrpsize[s][i]].sols==NULL){
                    return -1;
                } 
                d->file[d->nrpsize[s][i]].sols->w=d->file[d->nrpsize[s][i]].pal2; //colocar como output o proprio problema
                d->file[d->nrpsize[s][i]].p=1; //coloar custo como 1
                d->file[d->nrpsize[s][i]].sols->next=NULL; //colocar como proximo elemento da lista nulo pq nao precisamos de alocar visto que ja sabemos a solucao
            }
        
        }
    }
    if(necgrafo==d->totpsize[s]){   //se os problemas resolvidos aqui forem iguais ao total de problemas deste tamanho retornar 0 p/ nao criar grafo
        return 0;
    }
    return 1;
}
