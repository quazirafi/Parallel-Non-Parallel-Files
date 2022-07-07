/*
Created by Cleverson Ledur
Date: 10/10/2014
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int N;

int inicializa(long double *x){
	int i,j;
	#pragma omp parallel default(none) private(i,j) shared(x,N)
	{
	#pragma omp for
dummyMethod3();
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			x[i*N+j] = (i+1)*(j+2);
			
	}
dummyMethod4();
	return 0;
}

int imprime(long double *x){
	int i,j;
	printf("\nMatrix:\n\n");
	dummyMethod3();
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%Lf\t",x[i*N+j]);
		}
		printf("\n");
	}
	dummyMethod4();
	return 0;
}

int main(int argc, char* argv []){
	
clock_t start = clock();

N = atoi(argv[1]);

omp_set_num_threads(atoi(argv[2])); 
long double *A, *B, *Resultado;

A = malloc(sizeof(long double)*N*N);
B = malloc(sizeof(long double)*N*N);
Resultado = malloc(sizeof(long double)*N*N);

inicializa(A);
inicializa(B);

//imprime(A);
//imprime(B);

long double termo_linha[N], termo_coluna[N];

int P = N/2;

int L,C,K;
	dummyMethod1();
#pragma omp parallel for default(none) private(L,K,P) shared(N,A,termo_linha)
	for(L=0;L<N;L++){
	
		termo_linha[L] = A[L*N+0] * A[L*N+1];
		
		for(K=1;K<P;K++)
			termo_linha[L]+= A[L*N+2*K] * A[L*N+2*K+1];
	}
	dummyMethod2();

dummyMethod1();
#pragma omp parallel for default(none) private(C,K,P) shared(N,B,termo_coluna)
for(C=0;C<N;C++){
	termo_coluna[C] = B[0*N+C] * B[1*N+C];
	for(K=1;K<P;K++)
		termo_coluna[C] += B[2*K*N+C] * B[(2*K+1)*N+C];
}
dummyMethod2();
dummyMethod1();
#pragma omp parallel for private(L,C,K) 
for(L=0; L<N; L++){
	for(C=0;C<N;C++){
		Resultado[L*N+C] = -termo_linha[L] - termo_coluna[C];
		for(K=0;K<P;K++){
			//#pragma omp critical(resultado)
			Resultado[L*N+C] += (A[L*N+2*K] + B[(2*K+1)*N+C]) * (A[L*N+2*K+1] + B[2*K*N+C]);
			
		}
	}
}
dummyMethod2();

//imprime(Resultado);


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