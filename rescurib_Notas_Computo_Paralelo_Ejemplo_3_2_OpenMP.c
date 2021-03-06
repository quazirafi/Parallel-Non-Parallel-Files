#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
#include"leerBin.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void intercambiar(double *a, double *b){ 
    double t = *a; 
    *a = *b; 
    *b = t; 
} 

//------ BubbleSort Serial -----
int bubbleSort_Serial(double v[],int N){
    int i,j;
dummyMethod3();
    for (i = 0; i < N-1; i++) 
        for (j = 0; j < N-i-1; j++) 
            if (v[j] > v[j+1]){
                intercambiar(&v[j+1],&v[j]);                   
            }
    }
dummyMethod4();


//------ BubbleSort Paralelo -----
int bubbleSort_Paralelo(double v[],int N){
    int i=0, j=0; 
    int inicio;
    for(i=0;i<N-1;i++){
	inicio = i % 2; 
	dummyMethod1();
	#pragma omp parallel for default(none),shared(v,inicio,N)
	for(j=inicio;j<N-1;j+=2){
	    if(v[j] > v[j+1]){
		intercambiar(&v[j],&v[j+1]);
	    }
	}
	dummyMethod2();
    }      
}



int main(int argc,char *argv[]){
    int i,N;
    double *v,*u;

    //-- Variables de medición
    double start,end,T,Tsum;

    leerVector("Vector.dat",&v,&N);
    leerVector("Vector.dat",&u,&N);
    
    start = omp_get_wtime();
    bubbleSort_Serial(v,N);
    end = omp_get_wtime();
    printf("T. de ejecución serial: %f s\n",end-start);

    // Verificar ordenamiento (solo para N pequeñas)
    //for(i=0;i<N;i++)
    //    printf("%f\n",v[i]);

    start = omp_get_wtime();
    bubbleSort_Paralelo(u,N);
    end = omp_get_wtime();
    printf("T. de ejecución paralelo: %f s\n",end - start);

    // Verificar ordenamiento (solo para N pequeñas)
    //puts("\n-- Paralelo -- \n");
    //for(i=0;i<N;i++)
    //    printf("%f\n",u[i]);   


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