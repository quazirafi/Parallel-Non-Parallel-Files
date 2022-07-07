#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[])
{

  // Initialize arrays 
  int size=1000000;
  int *a = (int *)malloc(size*sizeof(int));
  int *b = (int *)malloc(size*sizeof(int));
  int *c = (int *)malloc(size*sizeof(int));

  // Time the parallel for-loop
  double start,end;
  start = omp_get_wtime();

  // Fill with a & b with random numbers between 0 and 100
  int i;
dummyMethod1();
#pragma omp parallel for
  for(i=0; i<size; i++)
  {
    a[i]=rand() % 100;
    b[i]=rand() % 100;
    c[i]=a[i]+b[i];
  }
dummyMethod2();

  end = omp_get_wtime();

  free(a);
  free(b);
  free(c);

  printf("Summed vectors a and b in %g seconds\n", end-start);

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