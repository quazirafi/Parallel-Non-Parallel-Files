#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){

	int index;
// Quite different from #pragma omp parallel by itself. 
dummyMethod1();
#pragma omp parallel for
	  for (index=0; index<10; index++){
	  printf("Hello world. I am %d of %d\n",omp_get_thread_num(),omp_get_num_threads());
dummyMethod2();
	  }
/*
	long sum = 0;
#pragma omp parallel for
	for (index=0; index<1000000; index++){
		sum++;
	}

	printf("Sum currently equals %ld\n",sum);
*/

/*
	long sum = 0;
	int j;
#pragma omp parallel for
	for (index=0; index<1000000; index++){
		for (j=0; j<10; j++){
			sum++;
		}
	}

	printf("Sum currently equals %ld\n",sum);
*/

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