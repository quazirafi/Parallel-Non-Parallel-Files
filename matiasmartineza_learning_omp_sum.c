#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
	int i;
	double tic = omp_get_wtime();
	omp_set_num_threads(2);
dummyMethod1();
	#pragma omp parallel for
	for (i = 1; i < 1000000; i++) {
		printf("%f\n", pow(i, 4));
	}
dummyMethod2();
	double toc = omp_get_wtime();
	printf("Tardó %f [s]\n", toc-tic);
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