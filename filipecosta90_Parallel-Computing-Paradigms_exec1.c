#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double f( double a ) {

  return (4.0 / (1.0 + a*a));
}

double pi = 3.141592653589793238462643;

int main() {
  double initial_time = omp_get_wtime();
  double mypi = 0;
  int n = 1000000000; // number of points to compute float h = 1.0 / n;
  float h = 1.0 / n;
dummyMethod1();
#pragma omp parallel for reduction (+:mypi) num_threads ( 6 )
  for(int i=0; i<n; i++) {
    mypi = mypi + f(i*h);
  }
dummyMethod2();
  mypi = mypi * h;
  printf("Aproximacao de pi = %.10f \n", (pi - mypi));
  double final_time = omp_get_wtime();
  printf("tempo de computação %.10f \n", final_time - initial_time );
  printf("resolução: %f\n", omp_get_wtick());
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