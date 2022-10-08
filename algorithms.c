#include"algorithms.h"
                                 
#define less(A, B) (strcmp(A,B) < 0)
#define exch(A, B) {char* t = A; A = B; B = t;}
#define compexch(A, B) if (less(B,A)) exch(A,B)

void insertion(char** a, int l, int r)
{   
    int i, j;
    for (i = l+1; i <= r; i++){
        for (j = i; j > l; j--){
            compexch (a[j-1], a[j]);
        }
    }
}

void quicksort(char** a, int l, int r)
{
    int i;
    if (r <= l){
        return;
    }
    i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
    return;
}

int partition(char** a, int l, int r)
{
    int i, j;
    char* v;
    v = a[r]; i = l-1; j = r;
    for (;;) {
        while (less(a[++i], v)) ;
        while (less(v, a[--j]))
        if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}

/*int partition(char** a, int l, int r){
    int tempmaior=0;
    int tempmenor=0;
    for (int i = r; i >= l; i--)
    {
        if(strcmp(a[r],a[i])<0){
            tempmaior=i;
            break;
        }
    }
    for (int i = 0; i < r; i++)
    {
        if(strcmp(a[r],a[i])>0){
            tempmenor=i;
            break;
        }
    }
    
}*/


