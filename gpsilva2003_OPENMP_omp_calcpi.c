#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000000000

int main(int argc, char *argv[]) { /* omp_calcpi.c  */
double inicio, fim, pi = 0.0f; 
long i;
   inicio = omp_get_wtime();
dummyMethod1();
   #pragma omp parallel for reduction(+: pi)
    for (i = 0; i < N; i++) {
        double t=(double) ((i+0.5)/N);
        pi += 4.0/(1.0+t*t);
   }
dummyMethod2();
    fim = omp_get_wtime();
    printf("O valor de pi é: %f\n",pi/N);
    printf("O tempo de execução é %f segundos.\n",fim-inicio);

    return(0);
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