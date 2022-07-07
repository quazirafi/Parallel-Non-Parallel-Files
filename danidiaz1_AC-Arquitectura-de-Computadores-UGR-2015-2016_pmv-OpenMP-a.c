// Compilar con -O2 y -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv){
	int i, j, f, c;
	double t1, t2, total;
	srand(time(NULL));

	//Leer argumento de entrada (no de componentes del vector)
	if (argc<2){
		printf("Falta tamaño de matriz y vector\n");
		exit(-1);
	}

	unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

	double *v1, *v2, **M;
	v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
	v2 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
	M = (double**) malloc(N*sizeof(double *));
	if ( (v1==NULL) || (v2==NULL) || (M==NULL) ){
		printf("Error en la reserva de espacio para los vectores\n");
		exit(-2);
	}

	dummyMethod3();
	for (i=0; i<N; i++){
		M[i] = (double*) malloc(N*sizeof(double));
		if ( M[i]==NULL ){
			printf("Error en la reserva de espacio para los vectores\n");
			exit(-2);
		}
	}
	dummyMethod4();
	//A partir de aqui se pueden acceder las componentes de la matriz como M[i][j]

	//Inicializar matriz y vectores
	//printf("Vector 1: \n\n[");

	dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<N; i++)
		v1[i]=rand()%(1-10 + 1) + 1;
	dummyMethod2();

	/*for (i=0; i<N; i++)
		printf("%.0lf ",v1[i]);*/

	//printf("]\n\n");

	//printf("Matriz: \n\n");

	dummyMethod1();
	#pragma omp parallel for
	for (f=0; f<N; f++)
		for (c=0; c<N; c++)
			M[f][c] = rand()%(1-10 + 1) + 1;
	dummyMethod2();


	/*for (f=0; f<N; f++)
	{
		printf("\n");
		for (c=0; c<N; c++)
			printf("%.0lf ", M[f][c]);
		
	}*/
	double suma;
	
	//Medida de tiempo
	t1 = omp_get_wtime();
		
	//Calcular producto de matriz por vector v2 = M · v1
	dummyMethod1();
	#pragma omp parallel for private(suma)
	for (f=0; f<N; f++)
	{
		suma=0;
		for (c=0; c<N; c++)
			suma += M[f][c] * v1[c];
		
		v2[f] = suma;
	}
	dummyMethod2();
	
	//Medida de tiempo
	t2 = omp_get_wtime();
	total = t2 - t1;

	//Imprimir el resultado y el tiempo de ejecución
	printf("Tiempo(seg.):%11.9f\t / Tamaño:%u\t/ V2[0]=%8.6f V2[%d]=%8.6f\n", total,N,v2[0],N-1,v2[N-1]);

	if (N<15)
	{
		printf("\nv2=[");
			dummyMethod3();
		for (i=0; i<N; i++)
			printf("%.0lf ",v2[i]);
			dummyMethod4();
		printf("]\n");
	}

	free(v1); // libera el espacio reservado para v1
	free(v2); // libera el espacio reservado para v2
	dummyMethod3();
	for (i=0; i<N; i++)
		free(M[i]);
	dummyMethod4();
	free(M);

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