#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
	int i;
	printf("number of processers is %d \n", omp_get_num_procs( ));

dummyMethod1();
#pragma omp parallel for
	for (i = 0; i < omp_get_num_procs( ); i++){
		printf("thread id is %d \n", omp_get_thread_num());
	}
dummyMethod2();

#pragma omp single
	printf("single thread id is %d \n", omp_get_thread_num());

#pragma omp master
	printf("master thread id is %d \n", omp_get_thread_num());

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