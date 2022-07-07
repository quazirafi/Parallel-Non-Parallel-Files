/* Andre Augusto Giannotti Scota (https://sites.google.com/view/a2gs/) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "openmp_util.h"

int main(int argc, char *argv[])
{
	/* #pragma omp parallel num_threads(3) */
	/* omp_set_num_threads(2); */

	dumpEnviroment();

dummyMethod1();
	#pragma omp parallel for ordered
	for(int i = 0; i < 20; ++i){

		#pragma omp ordered
		{
			if(i % 2 == 0)
				sleep(2);

			printf("Thread Id: [%d] - i: [%d]\n",omp_get_thread_num(), i);
		}
	}
dummyMethod2();

	return(0);
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