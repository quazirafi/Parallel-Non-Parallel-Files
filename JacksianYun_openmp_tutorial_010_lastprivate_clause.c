//010_lastprivate clause
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 4

int main(){

	int n = 8;
	int i,a, a_shared ;

	omp_set_num_threads(NUM_THREADS);

dummyMethod1();
	#pragma omp parallel for private(i) lastprivate(a) 
	for(i = 0 ; i< n ; i++){
		a = i + 1 ;
		printf(" Thread %d has a value of a = %d for i = %d\n", omp_get_thread_num(), a, i);
	}
dummyMethod2();

	printf("Value of a after parallel for: a = %d\n" , a);

	// lastprivate got a performance penalty. because the openmp library need keep track of execution
	// so, the last iter pass the value to shared variable, it is better than use lastprivate.
dummyMethod1();
	#pragma omp parallel for private(i,a) shared(a_shared)
	for (i=0; i<n ; i++){
		a = i + 1 ;
		printf(" Thread %d has a value of a = %d for i = %d\n", omp_get_thread_num(), a, i);
		if ( i == n - 1 ) a_shared = a;
	}
dummyMethod2();
    printf("Value of a after parallel for: a = %d\n", a_shared );
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