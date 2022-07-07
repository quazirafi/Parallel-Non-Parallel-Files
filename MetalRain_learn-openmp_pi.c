#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void) {

  long num_steps = 100000000;
  double step_size = 1.0/(double)num_steps;
  double pi = 0.0;
  double elapsed = omp_get_wtime();
dummyMethod1();
  #pragma omp parallel for reduction (+:pi) schedule(guided, 256)
  for(int i=0; i < num_steps; i++){
    double x = (i + 0.5) * step_size;
    pi += 4.0 / (1.0 + x*x);
  }
dummyMethod2();
  pi *= step_size;
  elapsed = omp_get_wtime() - elapsed;

  printf("PI: %g took %f seconds\n", pi, elapsed);
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