#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[]) {
	long dimension = 100000000;
	double initTime = omp_get_wtime();
	long sum1 = 0,sum2 = 0;
	int totalIteraciones = 900000000;
	int i;
dummyMethod1();
	#pragma omp parallel for reduction(+:sum1)
	for (i=0; i<totalIteraciones;i++) {
		sum1 = sum1 + i;
	}
dummyMethod2();
	printf("Suma: %ld\n", sum1+sum2);
	double endTime = omp_get_wtime();
	printf("Tiempo total tardado: %lf\n", endTime-initTime);

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