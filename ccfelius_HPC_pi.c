#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[])
{

  //initialize variables
  int i;
  double pi = 0;
  int niter = 2000000000;

  // Get timing
  double start,end;
  start=omp_get_wtime();

  // Calculate PI using Leibnitz sum
  /* Fork a team of threads */
dummyMethod1();
  #pragma omp parallel for reduction(+ : pi)
  for(i = 0; i < niter; i++)
  {
     pi = pi + pow(-1, i) * (4 / (2*((double) i)+1));
  } /* Reduction operation is done. All threads join master thread and disband */
dummyMethod2();

  // Stop timing
  end=omp_get_wtime();

  // Print result
  printf("Pi estimate: %.20f, obtained in %f seconds\n", pi, end-start);
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