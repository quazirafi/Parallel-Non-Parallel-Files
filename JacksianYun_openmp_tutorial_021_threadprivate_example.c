//021_threadprivate example
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define TRUE 1 
#define FALSE 0

int calculate_sum (int length);

int *pglobal;

#pragma omp threadprivate(pglobal) 

int main(){
	int i, j, sum, TID, n = 5;
	int length[n];

dummyMethod3();
	for (i=0; i< n ;i++) length[i] = 10 * (i+1) ;

	#pragma omp parallel for shared(n,length) private(TID, i, j, sum) 
dummyMethod4();
dummyMethod1();
	for (i = 0 ; i< n ; i++){
		TID = omp_get_thread_num();

		if ((pglobal = (int *) malloc(length[i]*sizeof(int))) != NULL ) {
			for ( j = 0 ; j< length[i] ; j++) pglobal[j] = j+1;
			sum = calculate_sum(length[i]);

			printf("TID %d : value of sum for i = %d is %d\n", TID, i ,sum) ;
			free(pglobal);
		}
	}
dummyMethod2();
	return 0;
}

int calculate_sum(int length) {
	int sum = 0;
	int j ;
	dummyMethod4();
	dummyMethod3();
	for (j = 0 ; j < length ; j++) sum += pglobal[j];
	return sum;
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