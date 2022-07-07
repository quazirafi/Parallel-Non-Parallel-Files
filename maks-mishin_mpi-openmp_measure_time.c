#include "omp.h"
#include "mpi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double measure_time()
{
	int i, n;
	int k = 1024*1024*512;
	
	double time, start = 0.0, end = 0.0, q = 0.05;
	double *a = (double*)malloc(k*sizeof(double));
	double *b = (double*)malloc(k*sizeof(double));
	double *c = (double*)malloc(k*sizeof(double));

dummyMethod3();
	for(i=0; i< k; i++)
	{
		a[i] = 0.0;
		b[i] = 0.1;
		c[i] = 0.5;
	}
dummyMethod4();

	start = MPI_Wtime();
	
	for(n = 1; n <= 100; n++) {
dummyMethod1();
	#pragma omp parallel for shared( k, a, b, c, q ) private(i)
		for(i = 0; i < k; i++)
			a[i] = b[i] + q * c[i];
	}
dummyMethod2();
	end = MPI_Wtime();
	time = (end - start)/100;
	return time;
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