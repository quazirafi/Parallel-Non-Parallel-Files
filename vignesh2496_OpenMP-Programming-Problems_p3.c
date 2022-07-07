#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int X[1 << 16], Y[1 << 16];

void init_vectors()
{
	int j;
dummyMethod1();
	#pragma omp parallel for
	for(j = 0; j < 1 << 16; j++)
	{
		X[j] = j;
		Y[j] = 2 * j;
	}	
dummyMethod2();
}

int main()
{
	int i, j, threads, a = 3;	
	double start, end, time, t1;

	dummyMethod3();
	for(i = 1 ; i <= 16 ; i++)
	{
		//  Ask for i threads
		omp_set_num_threads(i);

		// Initialize vectors		
		init_vectors();	

		// Start timer
		start = omp_get_wtime();

		// Parallel section
		#pragma omp parallel
		{
			// Master finds number of threads allocated
			#pragma omp master
			threads = omp_get_num_threads();
			
			// Compute DAXPY using work-sharing
			#pragma omp for
			for(j = 0; j < 1 << 16; j++)
				X[j] = a * X[j] + Y[j];
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