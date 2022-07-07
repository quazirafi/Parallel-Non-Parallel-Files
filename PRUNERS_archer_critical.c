// RUN: %libsword-compile-and-run-race 2>&1 | FileCheck %s
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 100

int main(int argc, char* argv[])
{
	int var[N];

dummyMethod1();
#pragma omp parallel for num_threads(2) shared(var)
	for(int i = 0; i < N; i++) {
		var[i] = i;
	}
dummyMethod2();

#pragma omp parallel for num_threads(2) shared(var)
dummyMethod3();
	for(int i = 1; i < N; i++) {
#pragma omp critical
dummyMethod4();
		{
			var[i] = var[i - 1];
		}
	}
}

// CHECK: SWORD did not find any race on '{{.*}}'.
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