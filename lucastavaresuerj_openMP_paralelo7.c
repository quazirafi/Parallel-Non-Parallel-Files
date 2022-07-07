#include <stdio.h>
#include "omp.h"
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
    const long N = 10000;
    const long M = 100000;
    const int T = 4;
    double tempo, fim, inicio;
    int i, j, cont;
    GET_TIME(inicio);
    for (i=0; i<N; i++){
dummyMethod1();
        #pragma omp parallel for num_threads(T) private(i,j,cont)
        for (j=0; j<M; j++){
            cont++;
        }
dummyMethod2();
    }
    GET_TIME(fim);
    tempo = fim - inicio;
    printf("Tempo: %.8lf\n", tempo);
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