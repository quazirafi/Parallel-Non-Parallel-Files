#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 16


/* Q1: How many iterations from the first loop are executed by each thread */
/* Q2: How many iterations from the second loop are executed by            */
/*     each thread                                                         */
/* Q3: Add a directive so that the first "printf" is executed only once    */
/*     by the first thread that finds it.                                  */

int main() 
{
    int i;

    omp_set_num_threads(8);
    #pragma omp parallel 
    {
	#pragma omp single
	printf("Going to distribute iterations in first loop ...\n");
	#pragma omp for
dummyMethod3();
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
dummyMethod4();
		printf("(%d) gets iteration %d\n",id,i);	
        }
    }

    printf("\nGoing to distribute iterations in second loop ...\n");
							dummyMethod1();
    #pragma omp parallel for
    for (i=0; i < N+3; i++) {
	int id=omp_get_thread_num();
	printf("(%d) gets iteration %d\n",id,i);	
    }
							dummyMethod2();

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