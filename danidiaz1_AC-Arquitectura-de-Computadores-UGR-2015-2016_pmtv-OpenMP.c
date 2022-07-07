#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv){ 
	int i, j, f, c, intkind, chunk; 
	double t1, t2, total; 
	srand(time(NULL));
	omp_sched_t kind;

	//Leer argumento de entrada (no de componentes del vector) 
	if (argc<4){
		printf("Formato: programa tamaño_matriz sched_var chunk\n"); 
		exit(-1); 
	} 

	unsigned int N = atoi(argv[1]); intkind=atoi(argv[2]); chunk=atoi(argv[3]); 
        // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B) 

	double *v1, *v2, **M; 
	v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes 
	v2 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL 
	M = (double**) malloc(N*sizeof(double *)); 
	if ( (v1==NULL) || (v2==NULL) || (M==NULL) ){ 
		printf("Error en la reserva de espacio para los vectores\n"); 
		exit(-2); 
	}
 
	switch(intkind){ 
		 case 1: kind = omp_sched_static; 
		 break; 

		 case 2: kind = omp_sched_dynamic; 
		 break; 

		 case 3: kind = omp_sched_guided; 
		 break; 

		 case 4: kind = omp_sched_auto; 
		 break; 
	} 
	
	omp_set_schedule(kind,chunk);
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
	#pragma omp parallel for schedule(runtime)
	for (i=0; i<N; i++) 
	{	 
		v1[i]=i; 
		//printf("%.0lf ",v1[i]); 
	} 
	dummyMethod2();

	//printf("]\n\n"); 

	//printf("Matriz: \n"); 
	dummyMethod1();
	#pragma omp parallel for schedule(runtime)
	for (f=0; f<N; f++) 
	{ 
		//printf("\n"); 
		for (c=0; c<f; c++){
			M[f][c] = 0;
			//printf("%.0lf ", M[f][c]);
   		}

		for (c=f; c<N; c++) 
		{ 
			M[f][c] = rand()%(1-10 + 1) + 1; 
			//printf("%.0lf ", M[f][c]); 
		}
		//n++; 
	}	 
	dummyMethod2();
	//Medida de tiempo 
	t1 = omp_get_wtime(); 

	//Calcular producto de matriz triangular por vector v2 = M · v1
	dummyMethod1();
	#pragma omp parallel for schedule(runtime)
	for (f=0; f<N; f++) 
		for (c=f; c<N; c++) 
			v2[f] += M[f][c] * v1[c]; 	
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