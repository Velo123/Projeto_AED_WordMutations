#ifndef scan
#define scan

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char ***scandict(char *argv[],int* max_size, int* min_size);
void freedict(char*** dict,int* max_size,int* min_size);

#endif