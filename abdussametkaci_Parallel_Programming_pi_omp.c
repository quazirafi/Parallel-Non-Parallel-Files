#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000000000

double f(double x) { return 4.0 / ( 1.0 + x * x); }

int main(void) {
  
double h = 1.0 / (double)N;
double pi = 0.0;
int i;

dummyMethod1();
#pragma omp parallel for schedule(static) reduction(+:pi) private(i)
for (i = 0; i < N; i++) // loop 
   pi += f(i*h); // reduction


pi *= h;
dummyMethod2();

printf("pi = %.10f\n", pi);

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