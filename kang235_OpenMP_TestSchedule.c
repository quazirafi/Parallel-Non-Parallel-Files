#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_SIZE 4000

void doWork(int t) {
	sleep(t);
}

int* initWork(int n) {
	int i;
	int* wA = (int *)malloc(sizeof(int)*n);
dummyMethod3();
	for (i = 0; i < n; i++) {
		wA[i] = rand() % 2 * i / (n / 10);
	}
dummyMethod4();
	return wA;
}

void omp_scheduling(const int *w, const int type)
{
	int i;
	double start = omp_get_wtime();
	char *type_name = "";

	switch (type)
	{
	case 0:
	{
			dummyMethod1();
#pragma omp parallel for schedule(static) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}
			dummyMethod2();
		type_name = "schedule(static)";
		break;
	}
	case 1:
	{
			dummyMethod1();
#pragma omp parallel for schedule(static, 50) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}
			dummyMethod2();
		type_name = "schedule(static, 50)";
		break;
	}
	case 2:
	{
			dummyMethod1();
#pragma omp parallel for schedule(dynamic) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}
			dummyMethod2();
		type_name = "schedule(dynamic)";
		break;
	}
	case 3:
	{
			dummyMethod1();
#pragma omp parallel for schedule(dynamic, 50) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}
			dummyMethod2();
		type_name = "schedule(dynamic, 50)";
		break;
	}
	case 4:
	{
			dummyMethod1();
#pragma omp parallel for schedule(guided) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}
			dummyMethod2();
		type_name = "schedule(guided)";
		break;
	}
	default:
	{
			dummyMethod1();
#pragma omp parallel for schedule(static) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
			}
			dummyMethod2();
			type_name = "schedule(static)";
			break;
	}
	}

	double end = omp_get_wtime();
	printf("Time for %s = %.16g\n", type_name, end - start);
}

int main(int argc, char *argv[]) {
	int *w = initWork(ARRAY_SIZE);
	int i;

	dummyMethod3();
	for (i = 0; i < 5; ++i)
	{
		omp_scheduling(w, i);
	}
	dummyMethod4();
	free(w);

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