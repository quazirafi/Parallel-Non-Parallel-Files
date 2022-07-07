/*
compilation:
clang -pedantic -Wall -o omp-ser-cl omp-ser.c -fopenmp=libomp -fopenmp-targets=nvptx64-nvidia-cuda -L/usr/local/cuda/lib64 --cuda-path=/usr/local/cuda

minimal compilation command:
clang  -o omp-ser-cl omp-ser.c -fopenmp=libomp -fopenmp-targets=nvptx64-nvidia-cuda

source: based on "OpenMP Application Programming Interface Examples - Version 5.0.0 - November 2019"
Section 4.7.1 'Simple target data Construct'
*/
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (){
    const int N = 1000000;
    unsigned int i;
    unsigned int j;
    float *a;
    float *b;
    float *c;

    a = (float *)malloc(N * sizeof(float));
    b = (float *)malloc(N * sizeof(float));
    c = (float *)malloc(N * sizeof(float));
        //srand((unsigned int)time(NULL));

dummyMethod3();
    for (i = 0; i < N; i++) {
        a[i] = 0;
        b[i] = ((float)rand() / (float)(RAND_MAX)) * 4.0;
        c[i] = ((float)rand() / (float)(RAND_MAX)) * 4.0;
    }
dummyMethod4();

    #pragma omp target data map (to: c[0:N], b[0:N]) map(from: a[0:N])
    {
        #pragma omp target
															dummyMethod1();
        #pragma omp parallel for
        for (j=0; j<N; j++)
        {
            a[j] = b[j]+3.73*c[j];
        }
															dummyMethod2();
    }

    return 0;
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