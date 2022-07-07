#include <stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 1024
#define N 1024

//Ejecutado con 8 hilos

int main(void){
    double A [M][N];
    double B [M][N];
    int i,j;
    double suma;

    //Preguntar a Arturo pq al paralelizar este bucle tarda más que si lo dejas sin paralelizar

dummyMethod3();
    for(i=0; i<M;i++){
        for(j=0; j<N; j++){
            A[i][j]=0.05;
            B[i][j]=0.5;
        }
    }
dummyMethod4();

    /*Original:*/
    #if 0
        for(i=0;i<M-1; i++){
            for(j=0;j<N;j++){
                A[i][j] = 2.0 * A[i+1][j]+B[i+1][j];
            }
        }
    #endif

    /*Como hay dependencia del valor de i para el cálculo 
    de la operación cambio el bucle de fuera por el de dentro*/
							dummyMethod1();
    #pragma omp parallel for shared(A,B), private(i,j)
    for(j=0;j<N;j++){
        for(i=0;i<M-1; i++){
            A[i][j] = 2.0 * A[i+1][j]+B[i+1][j];
        }
    }
							dummyMethod2();

    suma = 0.0;
    /*Región indeopendiente pq depende del bucle anterior
    La operación de suma requiere de una reducción*/
							dummyMethod1();
    #pragma omp parallel for shared(A,B), private(i,j), reduction(+:suma)
    for(i=0; i<M;i++){
        for(j=0; j<N; j++){
            suma = suma + A[i][j]+B[i][j];
        }
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