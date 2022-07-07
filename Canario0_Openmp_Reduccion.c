#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 1000

//Ejecutado con 8 hilos

int main(void)
{
    double A[M];
    double B[M];
    int i;
    double suma;

    //Preguntar a Arturo pq al paralelizar este bucle tarda más que si lo dejas sin paralelizar

dummyMethod3();
    for (i = 0; i < M; i++)
    {
        A[i] = 0.05;
        B[i] = 0.5;
    }
dummyMethod4();

    suma = 0.0;
/*Región indeopendiente pq depende del bucle anterior
    La operación de suma requiere de una reducción*/
dummyMethod1();
#pragma omp parallel for shared(A, B), private(i), reduction(+ : suma)
    for (i = 0; i < 1000; i++)
    {
        suma = suma + A[i] * B[i];
    }
dummyMethod2();

    printf("Suma %lf\n", suma);
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