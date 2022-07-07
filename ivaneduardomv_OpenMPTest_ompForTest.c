#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
	omp_set_num_threads(4);

dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < 32; ++i)
	{
		printf("Thread #%d is working. i = %d\n", omp_get_thread_num(), i);
	}
dummyMethod2();
	printf("Thread #%d is working.\n", omp_get_thread_num());
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