#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 10000000
#define REPEAT 500

int main (int argc, char *argv[]) {

  int i,j; 
  int *a, *b;

  a = (int*)malloc(N*sizeof(int));
  b = (int*)malloc(N*sizeof(int));

  /*
  ** Initialise the arrays in serial.
  */
dummyMethod3();
  for (i=0;i<N;i++) {
    a[i]=0;
    b[i]=rand();
  }    
dummyMethod4();

  /*
  ** Access in parallel.
  */
  for(j=0; j<REPEAT; j++) {
dummyMethod1();
#pragma omp parallel for
    for (i=0; i<N; i++) {
      a[i] = b[i];
    }
dummyMethod2();
  }

  free(a);
  free(b);

  return(EXIT_SUCCESS);
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