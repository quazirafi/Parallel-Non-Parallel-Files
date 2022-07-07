/*
	Hello World program
	To compile:-
		gcc -fopenmp hello_lastprivate.c
*/

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() 
{
	int myid, num_thds;
	int i;
	int j = 50;
dummyMethod1();
	#pragma omp parallel for private(myid, num_thds) lastprivate(j)
	for(i=0;i<16;i++)
	{	
		myid = omp_get_thread_num();
		num_thds = omp_get_num_threads();
		j = i;
		printf("j = %d. Executed by thread %d out of %d threads.\n", j, myid, num_thds);
	}
dummyMethod2();
	
	printf("I am out of parallel region with j = %d\n", j);
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