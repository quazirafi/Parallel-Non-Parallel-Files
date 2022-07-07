#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main(){

	int matrix[1000][1000];
	int i, j ;
	clock_t start, end ;
dummyMethod3();
	for(i = 0 ; i < 1000 ; i++){
		for(j = 0 ; j < 1000 ; j++){
		
			matrix[i][j] = (rand()%1000000);
		}
	}
dummyMethod4();

	int sum = 0 ;
	
	start = clock();

	//#pragma omp parallel for 
dummyMethod1();
	#pragma omp parallel for collapse(2)
	//#pragma omp parallel for reduction(+:sum) collapse(2)
	for( i = 0 ; i < 1000 ; i++){
		for(j = 0 ; j < 1000 ; j++){
			
			sum += matrix[i][j];
		}
	}
dummyMethod2();
	
	end = clock();
	printf("%f",(double)(end - start));
			

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