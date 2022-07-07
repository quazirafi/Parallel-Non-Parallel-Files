#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10000000

float sequential_reduction();
float omp_reduction();

int main(int argc, char *argv[]) {

	printf("Sequential reduction result: %f\n", sequential_reduction());
	printf("OMP reduction result: %f\n", omp_reduction());

	return 0;
}

float sequential_reduction()
{
	float sum = 0.0f;
	int i;
dummyMethod3();
	for (i = 0; i < SIZE; ++i)
	{
		sum += 1.0f / (i + 1);
	}
dummyMethod4();

	return sum;
}

float omp_reduction()
{
	float result = 0.0f;
	int i;

	dummyMethod1();
#pragma omp parallel for default(shared) private(i) reduction(+:result)
	for (i = 0; i < SIZE; ++i)
		result += 1.0f / (i + 1);
	dummyMethod2();

	return result;
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