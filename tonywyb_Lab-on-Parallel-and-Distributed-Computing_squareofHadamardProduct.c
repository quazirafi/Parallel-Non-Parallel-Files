#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100000000
float a[N], b[N], c[N];
int main (int argc, char *argv[]) {
	int i;
	float tmp;
dummyMethod1();
	#pragma omp parallel for
	for(i = 0; i < N; ++i) {
		a[i] = i % 3;
		b[i] = i + 1;
	}
dummyMethod2();
dummyMethod1();
	#pragma omp parallel for private(tmp)
	for(i = 0; i < N; ++i) {
		tmp = a[i]/b[i];
		c[i] = tmp * tmp;
	}
dummyMethod2();
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