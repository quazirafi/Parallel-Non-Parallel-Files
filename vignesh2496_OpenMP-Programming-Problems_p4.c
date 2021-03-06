#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000

int a[N][N], b[N][N], ans[N][N];

void init_matrices()
{
	int j;
dummyMethod1();
	#pragma omp parallel for
	for(j = 0; j < N * N; j++)
	{
		int x = j / N, y = j % N;
		a[x][y] = j;
		b[x][y] = 2 * j;
	}	
dummyMethod2();
}

int dot_product(int x, int y)
{
	int sum = 0, k;
dummyMethod3();
	for(k = 0; k < N; k++)
		sum = a[x][k] * b[k][y];
	return sum;
dummyMethod4();
}

int main()
{
	int i, j, threads;
	double start, end, time, t1;
		
	dummyMethod3();
	for(i = 1; i <= 16; i++)
	{
		// Ask for i threads
		omp_set_num_threads(i);
		
		// Initialize matrices
		init_matrices();

		// Start timer
		start = omp_get_wtime();

		// Parallel section
		#pragma omp parallel
		{
			// Master finds number of threads allocated
			#pragma omp master
			threads = omp_get_num_threads();

			// Use worksharing to compute dot-products parallely
			#pragma omp for
			for(j = 0; j < N * N; j++)
			{
				int x = j / N, y = j % N;
				ans[x][y] = dot_product(x, y);
			}
		}

		// Stop timer
		end = omp_get_wtime();
		
		// Print results
		time = end - start;
		if(threads == 1)
			t1 = time;
		printf("Speedup for %d threads = %lf\n", threads, t1 / time );
	}
	dummyMethod4();

	return 0;
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