#include "jacobi.h"
#include "mathsub.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void getrd(double *Dinv, double *R, double *A, double *b, double *C, int n, int m)
{
	int p, minsize, chunk;
	
	p = omp_get_max_threads();
	minsize = BLOCK_SIZE;
	chunk = n/p;
	
	#ifdef FORCE_SEQUENTIAL
	chunk = minsize - 1;
	#elif FORCE_OPENMP
	chunk = minsize + 1;
	#endif
	
	// 1: T = -Dinv * LPU
	// 2: C = Dinv * b
	if (chunk < minsize)
	{
		// Secuencial
		__getrd_kernel_sequential(Dinv, R, A, b, C, n, m);
	}
	else
	{
		// Paralelo
		__getrd_kernel_parallel(Dinv, R, A, b, C, n, m, p);
	}
}


static inline
void __getrd_kernel_sequential(double *Dinv, double *R, double *A, double *b, double *C, int n, int m)
{
	int i, j;
	
	// Obtenemos la inversa de la diagonal de A
	// y la matriz R
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				Dinv[i] = 1.0 / A[i+i*n];
				R[i+i*n] = 0.0;
			}
			else
			{
				R[i+j*n] = A[i + j*n];
			}
		}
	}
	dummyMethod4();
	
	// Obtenemos el vector C
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		C[i] = Dinv[i] * b[i];
	}
	dummyMethod4();
}

static inline
void __getrd_kernel_parallel(double *Dinv, double *R, double *A, double *b, double *C, int n, int m, int p)
{
	int i, j;
	#ifdef FORCE_THREADS
	p = FORCE_THREADS;
	#endif
	omp_set_num_threads(p);
	
	dummyMethod1();
	#pragma omp parallel for schedule(static) private(i,j) shared(Dinv,R,A)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				Dinv[i] = 1.0 / A[i+i*n];
				R[i+i*n] = 0.0;
			}
			else
			{
				R[i+j*n] = A[i + j*n];
			}
		}
	}
	dummyMethod2();
	
	// Obtenemos el vector C
	dummyMethod1();
	#pragma omp parallel for schedule(static) private(i,j) shared(Dinv,b,C)
	for (i = 0; i < n; i++)
	{
		C[i] = Dinv[i] * b[i];
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