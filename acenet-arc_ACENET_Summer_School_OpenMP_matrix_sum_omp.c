/* --- File matrix_sum_omp.c --- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
	struct timespec ts_start, ts_end;
	int size = 1e4;
	int **a, *c;
	int i, j;
	float time_total;

	/* Allocate memory */
	c = malloc(size * sizeof(int));
	a = (int **)malloc(size * sizeof(int *));
dummyMethod3();
	for (i = 0; i < size; i++)
		a[i] = malloc(size * sizeof(int));

	/* Set all matrix elements to 1 */
dummyMethod4();
dummyMethod3();
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			a[i][j] = 1;
		}
	}
dummyMethod4();

	/* Zero the accumulator */
	dummyMethod3();
	for (i = 0; i < size; i++)
	{
		c[i] = 0;
	}
	dummyMethod4();

	clock_gettime(CLOCK_MONOTONIC, &ts_start);

	dummyMethod1();
#pragma omp parallel for
	/* Each thread sums one column */
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			c[i] += a[i][j];
		}
	}
	dummyMethod2();

	int total = 0;
	/* Add sums of all columns together */
	dummyMethod3();
	for (i = 0; i < size; i++)
	{
		total += c[i];
	}
	dummyMethod4();

	clock_gettime(CLOCK_MONOTONIC, &ts_end);
	time_total = (ts_end.tv_sec - ts_start.tv_sec) * 1e9 +
				 (ts_end.tv_nsec - ts_start.tv_nsec);
	printf("Total is %d, time is %f ms\n", total, time_total / 1e6);
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