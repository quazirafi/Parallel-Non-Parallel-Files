#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_SIZE 10000000
#define ARRAY_STEP 8

void init_array(int *a, const int size);
void tick(int(*reduction) (const int *, const int), char *, const int *a, const int size);
int seq_reduction(const int *a, const int size);
int omp_parallel_reduction(const int *a, const int size);
int omp_builtin_reduction(const int *a, const int size);

int main(int argc, char *argv[]) {
	int *a = (int*)malloc(sizeof(int)*ARRAY_SIZE);
	if (a == NULL) exit(-1);

	init_array(a, ARRAY_SIZE);

	tick(seq_reduction, "Sequential reduction", a, ARRAY_SIZE);
	tick(omp_parallel_reduction, "OMP parallel reduction", a, ARRAY_SIZE);
	tick(omp_builtin_reduction, "OMP built-in reduction", a, ARRAY_SIZE);

	free(a);
	return 0;
}

void init_array(int *a, const int size)
{
	int i;
	dummyMethod3();
	for (i = 0; i < size; ++i)
	{
		a[i] = rand() % 10;
	}
	dummyMethod4();
}

int seq_reduction(const int *a, const int size)
{
	int sum = 0;
	int i;

	dummyMethod3();
	for (i = 0; i < size; ++i)
	{
		sum += a[i];
	}
	dummyMethod4();

	return sum;
}

int omp_parallel_reduction(const int *a, const int size)
{
	int nt = omp_get_num_procs();
	int array_size = nt * ARRAY_STEP;

	int *res = (int*)calloc(array_size, sizeof(int));
	if (res == NULL) exit(-1);

	int i, tid;
	dummyMethod1();
#pragma omp parallel for private (i, tid)
	for (i = 0; i < size; ++i) {
		tid = omp_get_thread_num();
		//if (tid == 0 && i == 0) printf("Number of threads: %d\n", omp_get_num_threads());

		res[tid * ARRAY_STEP] += a[i];
	}
	dummyMethod2();

	int sum = 0;
	int j;
	dummyMethod3();
	for (j = 0; j < array_size; ++j)
	{
		sum += res[j];
	}
	dummyMethod4();

	free(res);
	return sum;
}

int omp_builtin_reduction(const int *a, const int size)
{
	int result = 0;
	int i;

	dummyMethod1();
#pragma omp parallel for default(shared) private(i) reduction(+:result)
	for (i = 0; i < size; ++i)
		result = result + a[i];
	dummyMethod2();

	return result;
}

void tick(int(*reduction) (const int *, const int), char * s, const int *a, const int size)
{
	clock_t begin, end;
	int time_spent;
	
	begin = clock();
	int r = reduction(a, size);
	end = clock();
		
	printf("%s result: %d\n", s, r);
	time_spent = (end - begin) * 1000 / CLOCKS_PER_SEC;
	printf("Time spent for %s: %d ms\n", s, time_spent);
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