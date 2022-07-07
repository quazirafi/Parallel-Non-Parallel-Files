//Multiplicacion de dos matrices cuadradas
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void multiplicacion(int **a, int **b, int **c, int n){
	
	int i;
	omp_set_num_threads(4);
dummyMethod1();
	#pragma omp parallel for 
	for (i = 0; i < n; i++){
		int j;

		#pragma omp parallel for 		
		for(j = 0; j < n; j++){
			int k;

			for(k = 0; k < n; k++){
				c[i][j] += a[i][k]*b[k][j];                               
			}          
		}
	}	
dummyMethod2();
	
}


void imprimir(int **m, int n){
	dummyMethod3();
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");	
	}
	dummyMethod4();
}

void liberar(int **m, int n){
	dummyMethod3();
	for (int i = 0; i < n; i++){
	    free(m[i]);
		m[i] = NULL;
	}	
	dummyMethod4();
	free(m);
	m = NULL;
}

int main(int argc, char *argv[]){
	int n;
	n = atoi(argv[1]);
	clock_t begin, end;
	float time;
	
	int **a = (int **)malloc(n * sizeof(int *));
	int **b = (int **)malloc(n * sizeof(int *));
	int **c = (int **)malloc(n * sizeof(int *));

	dummyMethod3();
	for (int i = 0; i < n; i++){
		a[i] = (int *)malloc(n * sizeof(int));
		b[i] = (int *)malloc(n * sizeof(int));
		c[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++){
			a[i][j] = j+1;	
			b[i][j] = j+1;
			c[i][j] = 0;		
		}
	}
	dummyMethod4();
	
	begin = clock();
	multiplicacion(a, b, c, n);
	end = clock();

	time = (float)(end-begin);
	time = time/CLOCKS_PER_SEC;
	printf("%.6f\n", time/4);
	
	/*
	imprimir(a, n);
	printf("\n");
	imprimir(b, n);
	printf("\n");
	imprimir(c, n);*/
	

	liberar(a, n);
	liberar(b, n);
	liberar(c, n);

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