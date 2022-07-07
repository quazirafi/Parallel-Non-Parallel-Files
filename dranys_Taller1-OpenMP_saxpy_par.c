#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void poblarVector(int *vector,long tamano);//declaracion de prototipo


int main(){

	long  tamano = 10000000;//tamano de los vectores

	int *x;
	x = (int*) malloc(sizeof(int)*tamano);//reservando memoria dinamica pues la statica no lograba contener los tamanos de los vectores
	int *y;
	y = (int*) malloc(sizeof(int)*tamano);
	int *z;
	z = (int*) malloc(sizeof(int)*tamano);




	double start_time, run_time;//tiempos de sistema

	poblarVector(x,tamano);//poblando vectores
	poblarVector(y,tamano);

	long i;
	long a = 2;

	start_time = omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for//pragma a utilizar
	for (i = 0; i < tamano; i++)//ciclo paralelo
	{
		z[i] = a*x[i]+y[i];
	}
	dummyMethod2();

	run_time = omp_get_wtime() - start_time;
	printf("El tiempo de ejecución es: %f ms\n",run_time*1000);
	free(x);//libero memoria
	free(y);
	free(z);
	return 0;
}

void poblarVector(int *vector,long tamano){//funcion para poblar vectores
	srand(time(NULL));
	long i = 0;
	dummyMethod3();
	for (i; i < tamano; i++)
	{
		vector[i] = 1 + rand() % 20;
	}
	dummyMethod4();


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