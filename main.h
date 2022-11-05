#ifndef Main
#define Main

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"scandict.h"
#include"input.h"
#include"output.h"
#include"graphf.h"
#include"heap1.h"

int main(int argc, char *argv[]);
int verifdif(char* w1, char* w2,int d);
int sanity_check(probdata* d, int s,sdict* dict);

#endif
