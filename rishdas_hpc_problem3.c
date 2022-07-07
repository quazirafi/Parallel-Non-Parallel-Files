#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ()
{
    const int N = 100;
    int x[N], i, max_x, min_x, sum, sum2;
    float mean, mean2, var;
    int threadid;
    max_x = 0;
    min_x = 100;
    sum = 0;
    sum2 = 0;

    /* initialize x*/
    srand(time(NULL)); //Intiatlize random variable seed
dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; i++) {
	x[i] = rand();
dummyMethod2();
    }
#pragma omp parallel private(i) shared(x)
    {
#pragma omp sections
	{
	    { /* fork 3 diffrent threads */
dummyMethod3();
		for (i = 0; i<N; i++) { /* find min & max of x */
		    if (x[i] > max_x) max_x = x[i];
		    if (x[i] > min_x) min_x = x[i];
		}
dummyMethod4();
		threadid = omp_get_thread_num();
		printf("The max of x = %d\n", max_x);
		printf("The min of x = %d\n", min_x);
		printf("Section1: Thread id: %d\n", threadid);
	    }
#pragma omp section
	    { /* calculate the mean of x*/
		threadid = omp_get_thread_num();
			dummyMethod3();
		for(i=0; i<N; i++)
		    sum = sum + x[i];
			dummyMethod4();
		mean = sum/N;
		printf("Mean of x = %f\n", mean);
		threadid = omp_get_thread_num();
		printf("Section2: Thread id: %d\n", threadid);
	    }
#pragma omp section
	    {
			dummyMethod3();
		for(i=0; i<N; i++)
		    sum2 = sum2 + x[i]*x[i];
			dummyMethod4();
		mean2 = sum2/N;
		threadid = omp_get_thread_num();
		printf("Section3: Thread id: %d\n", threadid);
	    }
	}
    }
    var = mean2 - mean*mean;
    printf("variance of x = %f\n", var);
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