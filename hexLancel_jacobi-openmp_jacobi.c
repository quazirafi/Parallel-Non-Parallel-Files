#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "omp.h"
#include "jacobi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void copiar_array(double* array_a_copiar, double* otro_array, int tamanio){
dummyMethod3();
  for (int i = 0; i < tamanio; i++)
    otro_array[i] = array_a_copiar[i];
}
dummyMethod4();

void resolver_sistema_con_jacobi(double** matriz, int tamanio_matriz, double* b, double* solucion) {

	double ultima_iteracion[tamanio_matriz];

  //Lleno el array de 0 en paralelo
dummyMethod1();
  #pragma omp parallel for schedule(dynamic, 1) num_threads(1)
	for (int i = 0; i < tamanio_matriz; i++) {
		solucion[i] = 0;
	}
dummyMethod2();
  int k = 0;
	for (k; k < LIMITE_DE_ITERACIONES; k++){
    copiar_array(solucion, ultima_iteracion, tamanio_matriz);
		// Cada hilo procesa una fila
    //printf("Iteracion: %i\n", k+1);
			dummyMethod1();
		#pragma omp parallel for schedule(dynamic, 1)
		for (int i = 0; i < tamanio_matriz; i++){
			double sigma = 0;
			for (int j = 0; j < tamanio_matriz; j++){
				if (j != i) {
					sigma += matriz[i][j] * solucion[j];
          //printf("Sigma: %f \n", sigma);
				}
			}
			solucion[i] = (b[i] - sigma) / matriz[i][i];
      //printf("b[%i]=%2.f\n",i, b[i]);
      //printf("x[%i]=%2.f\n",i,solucion[i]);
		}
			dummyMethod2();

    //printf("\n");
    // Checking for the stopping condition ...
    int stopping_count = 0;
    for (int s = 0; s < tamanio_matriz; s++) {
      if (fabs(ultima_iteracion[s] - solucion[s]) <= EPSILON) {
        stopping_count++;
      }
    }
    if (stopping_count == tamanio_matriz) break;
	}
  //printf("Cantidad de iteraciones: %i\n", k+1);
  //printf("solucion 1 anterior: %f \n", ultima_iteracion[0]);
  //printf("Solucion 1: %f \n", solucion[0]);
  //printf("Diferencia: %f \n", fabs(ultima_iteracion[0] - solucion[0]));
  //printf("Solucion 2: %f \n", solucion[1]);
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