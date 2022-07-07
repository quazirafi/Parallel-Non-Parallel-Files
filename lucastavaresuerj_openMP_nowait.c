#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 100000000
#define M 100000000

void nowait_exemple(float *a, float *b, float *y, float *z){
    int i;
    #pragma omp parallel 
    {
        #pragma omp for nowait 
dummyMethod3();
        for (i=0; i<N; i++) {
            b[i] = (a[i] + a[i-1])/2.0;
        }
dummyMethod4();
        #pragma omp for nowait 
dummyMethod3();
        for (i=0; i<M; i++) {
            y[i] = z[i]*0.5;
        }
dummyMethod4();
    }
}

int main (){
    long i;
    const int T = 4;
    double tempo, fim, inicio;
    float *vet1, *vet2, *vet3, *vet4;
    vet1 = (float*) malloc(N*sizeof(float));
    vet2 = (float*) malloc(N*sizeof(float));
    vet3 = (float*) malloc(N*sizeof(float));
    vet4 = (float*) malloc(N*sizeof(float));
    //omp_set_num_threads(T);
    GET_TIME(inicio);
							dummyMethod1();
    #pragma omp parallel for num_threads(T)
    for(i=0; i<N; i++){
        vet1[i] = i;
        vet2[i] = N-i-1;
    }
							dummyMethod2();
    GET_TIME(fim);
    tempo = fim - inicio;
    printf("Tempo 1: %.8lf\n", tempo);
    GET_TIME(inicio);
							dummyMethod1();
    #pragma omp parallel for num_threads(T)
    for(i=0; i<M; i++){
        vet3[i] = i;
        vet4[i] = N-i-1;
    }
							dummyMethod2();
    GET_TIME(fim);
    tempo = fim - inicio;
    printf("Tempo 2: %.8lf\n", tempo);
    GET_TIME(inicio);
    nowait_exemple(vet1, vet2, vet3, vet4);
    GET_TIME(fim);
    tempo = fim - inicio;
    printf("Tempo 3: %.8lf\n", tempo);
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