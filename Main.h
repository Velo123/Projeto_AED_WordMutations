#ifndef Main
#define Main

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]);
char ***scandict(char *argv[],int* max_size, int* min_size);

void freedict(char*** dict,int* max_size,int* min_size);

#endif