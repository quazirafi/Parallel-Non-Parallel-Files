#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

long long fib_value[1000];


long long fib(long i){
	if(i == 0 || i == 1){
		return 1;
	}else{
		if(fib_value[i] != 0){
			return fib_value[i];
		}
		else{
			fib_value[i] = fib(i - 1) + fib(i - 2); 
			return fib_value[i];	
		}
	}
}


int main(){
	
	long long n=50;

	double start, end;
	long long i=0;

	// omp_set_num_threads(4);

	start = omp_get_wtime();
			dummyMethod1();
	#pragma omp parallel for private(i)
		for(i=0; i<n; i++){
			printf("Fib[%lld] = %lld\n", i, fib(i));
		}	
			dummyMethod2();
	end = omp_get_wtime();

	printf("Work took %f sec. time.\n", end-start);
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