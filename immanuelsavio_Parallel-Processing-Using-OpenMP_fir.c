#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void fir(float *input, float *output, float *coef, int numOfSamples, int numOfCoef) {
	int i, j;
dummyMethod1();
#pragma omp parallel for private(j)
	for (i = 0; i < numOfSamples; i++) {
		output[i] = 0;
		for (j = 0; j < numOfCoef; j++) {
			if (i-j >= 0) {
				output[i] += input[i-j] * coef[j];
			}
		}
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