#include <stdio.h>
#include <stdlib.h>
#include "functions3.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE_DATA (1024*1024*64*3)

static double MEM_CHUNK[SIZE_DATA];

// nueva Version algoritmo multiplicacion de matrices filas x filas (Una fila por Una fila)


int N, numT;
double *matrizA, *matrizB, *matrizC;



int main(int argc, char ** argv)
{
	
	int N = (int) atof(argv[1]); //Tamqano de la matriz
	int numT = (int) atof(argv[1]); // cantidad de hilos a emplear

//#pragma omp parallel 
{
	double *matrizA, *matrizB, *matrizC;
	matrizA = MEM_CHUNK;
	matrizB = matrizA + N*N;
	matrizC = matrizB + N*N;

	//Se deja que el hilo principal (maestro) haga las rutinas de inicializacion

//#pragma omp master 

	matrizInit(N, matrizA, matrizB, matrizC);
	/*printf("Impresion Matriz A :\n");
	/imprimirMatrices(N, matrizA);


	printf("Impresion Matriz B :\n");
	imprimirMatrices(N, matrizB);
	

	printf("Impresion Matriz B :\n");
	imprimirMatrices(N, matrizB);
	*/
	omp_set_num_threads (numT);
	sampleStart();
	
	//prueba de multiplicacon de matrices con OpenMP

	dummyMethod1();
#pragma omp parallel for
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			double *pA, *pB, suma =0.0;
			pA = matrizA+(i*N);//Fila
			pB = matrizB+(j*N); //Columna
			for(int k=0;k < N;k++, pA++, pB++){

				suma += (*pA * *pB);
			}
			matrizC[i*N+j] = suma;
		}
	}
	dummyMethod2();
	sampleStop();
	/*printf("Impresion Matriz C :\n");
	imprimirMatrices(N, matrizC);
	*/
}



printTime();
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