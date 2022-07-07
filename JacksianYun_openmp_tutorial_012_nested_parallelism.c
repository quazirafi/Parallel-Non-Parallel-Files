//012_nested parallelism
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 8

int main(){
	int n = 5;
	int a[n], b[n][n];
	int i, j;

	omp_set_nested(1);
	//omp_set_nested(0);

	#pragma omp parallel shared(n,a,b)
	{
		#pragma omp for 
		for(i = 0 ; i< n ; i++){
			a[i] = i + 1;
			//#pragma omp for //error
dummyMethod1();
			#pragma omp parallel for
			for ( j = 0 ; j < n ; j++){
				b[i][j] = a[i];
				printf("b[%d][%d] = %d, threads: %d\n", i,j,b[i][j],omp_get_thread_num());
			}
dummyMethod2();
		}
	}

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