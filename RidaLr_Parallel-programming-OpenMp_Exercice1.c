#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	
	double temps_debut=omp_get_wtime();
	//Exercice 1.1
	int ID=0;
	//#pragma omp parallel
	printf("Hello world (%d)",ID);
	printf("Hello World (%d)\n",ID);
	
	//Exercice 1.2
	
	int n=500;
	omp_set_num_threads(10);
dummyMethod1();
	#pragma omp parallel for
	for(int i=0;i<n;i++){
		
		printf("Hello world from thread number %d \n",omp_get_thread_num());
	}
dummyMethod2();
	//Compute execution time of parallel section 
	printf("Temps d'exécution  : %f\n",(omp_get_wtime() - temps_debut));
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