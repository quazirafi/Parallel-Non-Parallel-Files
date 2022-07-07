#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 99999999
int a[N];
int main (int argc, char *argv[]) {
	int i;
	int tmp = 0;
dummyMethod1();
	#pragma omp parallel for
	for(i = 0; i < N; ++i) {
		a[i] = i >> 1;
	}
dummyMethod2();
	a[65536 << 1] = 99999999 >> 1;
dummyMethod1();
	#pragma omp parallel for reduction(^:tmp)
	for(i = 0; i < N; ++i) {
		tmp = tmp^a[i];
	}
dummyMethod2();
	printf("%d\n", tmp);
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