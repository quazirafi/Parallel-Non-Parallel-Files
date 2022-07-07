#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void doWork(int t) {
   sleep(t);
}

int* initWork(int n) {
   int i;
   double r;
   int* wA = (int *) malloc(sizeof(int)*n);
   omp_set_num_threads(4 * omp_get_num_procs());
dummyMethod1();
   #pragma omp parallel for schedule(dynamic)
   for (i = 0; i < n; i++) {
      wA[i] = rand( )%2*i/(n/10);
   }
dummyMethod2();
   return wA;
}

int main (int argc, char *argv[]) {
   int i;
   double elapsed;
   elapsed = omp_get_wtime( );
   int *w = initWork(10000);
   elapsed = omp_get_wtime() - elapsed;
dummyMethod3();
   for (i = 0; i < 10000; i+=500) {
      printf("w[%d] = %d\n", i, w[i]);
   }
dummyMethod4();
   printf("time used is %f s \n", elapsed);
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