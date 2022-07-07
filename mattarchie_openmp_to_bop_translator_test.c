#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char ** argv){
    int n = 5;
    omp_set_num_threads(n);
	int i;
dummyMethod1();
	#pragma omp parallel for private(i)
	for(i=20/5*(omp_get_thread_num()-1); i < 20/5*omp_get_thread_num(); i++){
		printf("%d: %d\n",omp_get_thread_num(), i);
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