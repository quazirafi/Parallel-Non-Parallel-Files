/* Algoritmo de multiplicação de Matrizes (Sequencial)
Autor:	Cleverson Lopes Ledur
Data:	07/05/2013
*/	 

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define Width 835       //Tamanho da Matriz
#define NR_THREADS 10
void matrixMult(float M_h[Width*Width], float N_h[Width*Width], float P_h[Width*Width]){
 	
        
        int i,j,k,nthreads;
	
	#pragma omp parallel shared(M_h,N_h,P_h,nthreads) private(i,j,k) 
	{
		#pragma omp for	
dummyMethod3();
		for (i=0; i<Width; i++)
			for (j=0;j<Width;j++){
				float soma = 0;	
				for(k=0;k<Width; k++)
					soma += M_h[i*Width+k] * N_h[k*Width+j];
				P_h[i*Width+j] = soma;
		}
dummyMethod4();
	}
}

void inicia(float x[Width*Width]){
        int i,j;
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<Width; i++)
            for(j=0; j<Width; j++)
                x[i*Width+j] = rand()%100;
}
dummyMethod2();

void limpa(float x[Width*Width]){
        int i,j;
	dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<Width; i++)
            for(j=0; j<Width; j++)
                x[i*Width+j] = 0;
	dummyMethod2();
}

void imprime(float x[Width*Width]){
        int i,j;
	#pragma omp for  
	dummyMethod3();
	for (i=0; i<Width; i++){
            for(j=0; j<Width; j++)
                printf("%.0f\t|", x[i*Width+j]);
	    printf("\n");
	}
	dummyMethod4();
	printf("\n");
}

int main(){

    	srand(time(NULL));	//Para os números aleatórios

    	float M_h[Width*Width], N_h[Width*Width], P_h[Width*Width];
    
    	//Inicia Matriz M e N com valores aleatórios
    	inicia(M_h);
    	inicia(N_h);

    	//Preenche com 0 a matriz Produto
    	limpa(P_h);
    	
    	//Chama a função de multiplicação 
    	matrixMult(M_h, N_h, P_h);   
	//imprime(M_h);
	//imprime(N_h);
	//imprime(P_h);

	
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