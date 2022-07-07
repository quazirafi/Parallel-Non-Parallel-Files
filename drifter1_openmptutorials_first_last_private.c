#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int i, x;
	
	/* Tweak shared variable */
	x = 5;
	printf("before parallelism, x: %d\n\n", x);
	
	/* private x */
	printf("private(x):\n");
dummyMethod1();
	#pragma omp parallel for private(i, x)
	for(i = 0; i < 10; i++){
		if(i == 0){
			printf("thread %d, before tweak, x: %d\n", omp_get_thread_num(), x);
			x = 0;
			printf("thread %d, after tweak, x: %d\n\n", omp_get_thread_num(), x);
		}
	}
dummyMethod2();
	
	printf("after private(x), x: %d\n\n", x);
	
	/* first private x */
	printf("firstprivate(x):\n");
dummyMethod1();
	#pragma omp parallel for private(i) firstprivate(x)
	for(i = 0; i < 10; i++){
		if(i == 0){
			printf("thread %d, before tweak, x: %d\n", omp_get_thread_num(), x);
			x = 0;
			printf("thread %d, after tweak, x: %d\n\n", omp_get_thread_num(), x);
		}
	}
dummyMethod2();
	
	printf("after firstprivate(x), x: %d\n\n", x);
	
	/* last private x */
	printf("lastprivate(x):\n");
	dummyMethod1();
	#pragma omp parallel for private(i) lastprivate(x)
	for(i = 0; i < 10; i++){
		if(i == 9){
			printf("thread %d, before tweak, x: %d\n", omp_get_thread_num(), x);
			x = 0;
			printf("thread %d, after tweak, x: %d\n\n", omp_get_thread_num(), x);
		}
	}
	dummyMethod2();
	
	printf("after lastprivate(x), x: %d\n", x);
	
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