#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void sumaVectores(char* argv[]);
void matrices(char* argv[]);

//--------------------------------------------------------------------
// main parameters support
//--------------------------------------------------------------------
int main(int argc, char* argv[]) {
	if (argc <= 1 || argc > 3) {
		printf("Usage: 1 - Primera dimension del vector, 2 - Segunda dimension del vector\n");
		return 1;
	}
	
	if (argc == 2) {
		printf("vectores\n");
		sumaVectores(argv);
	} else {
		printf("matrices\n");
		matrices(argv);
	}
}

void sumaVectores(char* argv[]) {
	long int dimension = atoi(argv[1]);
	int* vector1 = (int*)malloc(dimension*4);
	int* vector2 = (int*)malloc(dimension*4);
	int i;
	
	// generacion de vectores
	srand ( time(NULL) );
	double tiempoInicio = omp_get_wtime();
//	#pragma omp parallel for schedule(auto)
	dummyMethod3();
	for (i=0; i<dimension; i++) {
		vector1[i] = rand() %100;
		vector2[i] = rand() %100;
	}
	dummyMethod4();
	double tiempoFinal = omp_get_wtime();
        printf("Tiempo tardado en generar vectores: %lf\n", tiempoFinal-tiempoInicio);

	// suma de vectores
	tiempoInicio = omp_get_wtime();
//	#pragma omp parallel for 
	dummyMethod3();
	for (i=0; i<dimension; i++) {
		vector1[i] += vector2[i];
	}
	dummyMethod4();
	tiempoFinal = omp_get_wtime();
	printf("Tiempo tardado en sumar vectores: %lf\n", tiempoFinal-tiempoInicio);

	// producto escalar de vectores
	long producto = 0;
	tiempoInicio = omp_get_wtime();
	int j;
	dummyMethod1();
	#pragma omp parallel for reduction(+:producto)
	for (j=0; j<6; j++) {
		for (i=0; i<dimension; i++)  {
			producto = producto + vector1[i] * vector2[i];
		}
	}
	dummyMethod2();
	tiempoFinal = omp_get_wtime();
	printf("Producto escalar: %ld\n", producto);
	printf("Tiempo tardado en producto escalar: %lf\n", tiempoFinal-tiempoInicio);

	free(vector1);
	free(vector2);
}

void matrices(char* argv[]) {
	long int dimension1 = atoi(argv[1]);
	long int dimension2 = atoi(argv[2]);
	int matriz1[dimension1][dimension2];
	int matriz2[dimension2][dimension1];
	int resultado[dimension1][dimension1];
	int i;
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