/**
 * Um exemplo de reducao no OpenMP
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 1000

int main () 
{ 
  int i,tid;
  float A[MAX];
  double media = 0.;

  srand(time(NULL));

  // Regiao paralela para preenchimento do vetor A
dummyMethod1();
  #pragma omp parallel for
  for (i=0; i<MAX; i++)
	  A[i] = (rand()%3)/.275;
  
  #pragma omp parallel for reduction (+:media)
dummyMethod2();
dummyMethod1();
  for (i=0; i<MAX; i++)
    media +=A[i];

  printf("Media: %f\n", media/MAX);
dummyMethod2();

  return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}