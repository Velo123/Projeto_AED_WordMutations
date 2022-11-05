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
    return;
}

void quicksort(char** a, int l, int r)
{
    int i;
    if (r<=l){
        return;
    }
    i = partition(a, l, r);
    if(r-l<=15)
    {
        insertion(a,l,r);
    }
    else if (i-l<r-i)
    {
        quicksort(a, l, i-1);
        quicksort(a, i+1, r);
    }
    else
    {
        quicksort(a, i+1, r);
        quicksort(a, l, i-1);
    }
    return;
}

char* med3(char** p,int l,int r){
    char* a=p[l];
    char* b=p[(l+r)/2];
    char* c=p[r];
    if (strcmp(a,b)<0 && strcmp(a,c)<0)
    {
        if (strcmp(b,c)<0)
        {
            return b;
            
        }
        else
        {
            return c;
        }
    }
    else if (strcmp(b,a)<0 && strcmp(b,c)<0)
    {
        if (strcmp(a,c)<0)
        {
            return a;
            
        }
        else
        {
            return c;
            
        }
    }
    else if (strcmp(b,a)<0 && strcmp(b,c)<0)
    {
        if (strcmp(a,b)<0)
        {
            return a;
            
        }
        else
        {
            return b;
            
        }
    }
    return c;
}


int partition(char** a, int l, int r)
{
    int i, j;
    char* v;
    v = a[r];
    i = l-1; j = r;
    for (;;) {
        while (less(a[++i], v));
        while (less(v, a[--j]))
        if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}