//Ejercicio 1
#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char*argv[]){
 double *A;
 int i,j;
 int check = 1; 
 
 int numThreads = atoi(argv[2]);
 int N=atoi(argv[1]);
 omp_set_num_threads(numThreads);

 //Aloca memoria para la matriz
  A=(double*)malloc(sizeof(double)*N*N);
 
 //Inicializa la matriz. Cada posicion debe quedar con el valor I*J
 // I => fila J=> columna. 

  for(i=0;i<N;i++){
dummyMethod1();
   #pragma omp parallel for shared(A) firstprivate(i)
   for(j=0;j<N;j++){
		A[i*N+j]=i*j;
dummyMethod2();
   }
  }   

 //Verifica el resultado
  for(i=0;i<N;i++){
   for(j=0;j<N;j++){
	   check=check&&(A[i*N+j]==i*j);
   }
  }   

  if(check){
   printf("Resultado correcto\n");
  }else{
   printf("Resultado erroneo \n");
  }

 free(A);

 return(0);
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