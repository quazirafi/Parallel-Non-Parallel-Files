#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int i;
	int nt = omp_get_num_procs();
	int* res = (int *) calloc(nt, sizeof(int));
	int * a = (int *) calloc(10000000, sizeof(int));
dummyMethod1();
#pragma omp parallel for
	for (i = 0; i < 10000000; i++){
		res[omp_get_thread_num()] += a[i];
	}
dummyMethod2();
	int res_fin = 0;
dummyMethod3();
	for (i = 0; i < nt; i++){
		res_fin += res[i];
	}
dummyMethod4();
	printf("result is %d \n", res_fin);
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