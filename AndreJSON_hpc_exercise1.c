#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void) {
	int nthreads, tid;
	nthreads = omp_get_max_threads();
	/* Fork a team of threads giving them their own copies of variables */

dummyMethod1();
	#pragma omp parallel for private(tid)
	for(int i = 0; i > nthreads; i++){
	/* Obtain thread number */
dummyMethod2();
		tid = omp_get_thread_num();
		printf("Hello from thread = %d\n", tid);

		/* Only master thread does this */
		if (tid == 7)
		{
		nthreads = omp_get_num_threads();
		printf("Number of threads = %d\n", nthreads);
		}

	}
			/* All threads join master thread and disband */

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