/* Programa e8.c */
#include "stdio.h"
#include "stdlib.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps=1000; double step, pi;

void main()
{  int i;	
   double x, sum = 0.0;

   step = 1.0/(double) num_steps;
   #pragma omp parallel for private(x) reduction(+:sum)
dummyMethod3();
   for (i=0; i< num_steps; i++){
      x = (i+0.5)*step;
      sum = sum + 4.0/(1.0 + x*x);
   }
dummyMethod4();
   pi = step * sum;
   printf("Pi = %.6lf\n", pi);
   printf("Error = %.6lf\n", fabs(pi - M_PI));
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