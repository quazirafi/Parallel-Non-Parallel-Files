#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 5

/* Q1: Which iterations of the loops are executed by each thread     */
/*     when the collapse clause is used?                             */
/* Q2: Is the execution correct if we remove the collapse clause?    */
/*     Add the appropriate clause to make it correct.                */

int main() 
{
    int i,j;

    omp_set_num_threads(8);
dummyMethod1();
    #pragma omp parallel for private(j) // collapse(2)
    for (i=0; i < N; i++) {
       for (j=0; j < N; j++) {
	  int id=omp_get_thread_num();
dummyMethod2();
	  printf("(%d) Iter (%d %d)\n",id,i,j);	
	}
    }

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