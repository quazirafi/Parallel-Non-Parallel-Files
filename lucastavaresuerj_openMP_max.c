#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100000000

int main() {
    long max_val = 0;
    long i;
    long* vet;
    int T = 4;
    double inicio, fim, fim2, tempo1, tempo2;
    GET_TIME(inicio);
    vet = (long*) malloc(N * sizeof(long));
dummyMethod1();
    #pragma omp parallel for num_threads(T)
    for(i=0; i<N; i++) {
        vet[i] = i;
    }
dummyMethod2();
    vet[100] = 299999999;
    GET_TIME(fim);
dummyMethod1();
    #pragma omp parallel for reduction(max:max_val) num_threads(T) 
    for(i=0;i<N;i++) {
        if(vet[i] > max_val) {
            max_val = vet[i];
        }
    }
dummyMethod2();
    GET_TIME(fim2);
    tempo1 = fim - inicio;
    tempo2 = fim2 -inicio - tempo1;
    printf("\ntempo1: %lf\n",tempo1);
    printf("\ntempo2: %lf\n",tempo2);
    printf("\ntempo total: %lf\n",tempo2+tempo1);
    printf("\nmax_val = %ld\n", max_val);
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