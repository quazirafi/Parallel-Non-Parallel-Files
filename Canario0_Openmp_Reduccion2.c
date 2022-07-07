#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 1000
#define INT_MAX 999

//Ejecutado con 8 hilos

int main(void)
{
    int A[M];
    int i;
    int result= INT_MAX;

    //Preguntar a Arturo pq al paralelizar este bucle tarda más que si lo dejas sin paralelizar

dummyMethod3();
    for (i = 0; i < M; i++)
    {
        A[i] = i;
    }
dummyMethod4();

        /* M ́ınimo de valores en un array */
dummyMethod1();
#pragma omp parallel for shared(A) reduction(min : result)
    for (i = 0; i < 1000; i++)
    {
        if (A[i] < result)
            result = A[i];
    }
dummyMethod2();
    printf("Suma %d\n", result);
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