#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "mm.h"
#define _UNROLL_FACT_ 1
#define NTIMES 100
void triad_1loop_gpuoffload(int gpuid)
{
	ssize_t j = 0;
	
	printf("Inside triad_1loop_gpuoffload() %d, gpuid: %d \n", array_size, gpuid);
	//int uloop = _UNROLL_FACT_;
	//printf("uloop : %d \n", uloop);
	
	#pragma omp target data map (to: c[0:array_size], b[0:array_size]) map(tofrom: a[0:array_size]) device(gpuid)
dummyMethod1();
	#pragma omp target teams distribute parallel for device(gpuid)
//	#pragma omp target teams distribute parallel for simd
	#pragma unroll _UNROLL_FACT_
    for (j=0; j<array_size; j++)
	{
        a[j] = b[j]+scalar*c[j];
	}
dummyMethod2();
}

void triad_2loop_gpuoffload(int row, int col)
{
	int i = 0;	
	int j = 0;
	int k = 0;
	
	#pragma omp target data map (to: c[0:array_size], b[0:array_size]) map(to: a[0:array_size]) 
	for(k=0; k<NTIMES; k++)
	{
	dummyMethod1();
	#pragma omp target teams distribute parallel for private(i, j) collapse(2)
	for(i=0; i<row; i++)
	{
		for (j=0; j<col; j++)
		{
//			printf("array_index:(%d:%d) => a[%d], %lf \n", i, j, (i*columns +j), a(i,j));
        	a(i,j) = b(i,j) + scalar * c(i,j);
		}
	}
	dummyMethod2();
	}
}

/*
 * Collapseing the loop improves performance by ~35 times than without collapsing.
 * */
/*
void matrix_multiplication_gpuoffload(int gpuid)
{
	int i = 0;
	int j = 0;
	int k = 0;

	printf("Inside matrix_multiplication_gpuoffload %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE, gpuid);
	#pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(gpuid)
	#pragma omp target device(gpuid)
	#pragma omp teams distribute parallel for collapse(2) private(i,j,k) 
	for(i=0;i<ROWSIZE;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
	}	
}
*/
void matrix_multiplication_gpuoffload(int gpuid, int np, int pid, double *pA, double *pC)
{
	int i = 0;
	int j = 0;
	int k = 0;

	printf("Inside MPI matrix_multiplication_gpuoffload %dx%d, pid : %d, gpuid: %d \n", ROWSIZE,COLSIZE, pid, gpuid);
	#pragma omp target data map (to: pA[0:ROWSIZE/np*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE/np*COLSIZE]) device(gpuid)
	#pragma omp target device(gpuid)
	dummyMethod1();
	#pragma omp teams distribute parallel for collapse(2) private(i,j,k) 
	for(i=0;i<ROWSIZE/np;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
	}	
	dummyMethod2();
}

void matrix_multiplication_gpuoffload_UVM(int gpuid)
{
        int i = 0;
        int j = 0;
        int k = 0;

        printf("Inside matrix_multiplication_gpuoffload_UVM %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE,  omp_get_default_device());


 
															dummyMethod1();
        #pragma omp  target teams distribute parallel for collapse(2) private(i,j,k)  is_device_ptr(pA, pB, pC) 



        for(i=0;i<ROWSIZE;i++)
        {
                for(j=0;j<COLSIZE;j++)
                {
                        for(k=0;k<ROWSIZE;k++)
                        {
                                pC(i,j)+=pA(i,k)*pB(k,j);
                        }
                }
        }
															dummyMethod2();

}
void matrix_multiplication_gpuoffload_multigpu()
{
        int i = 0;
        int j = 0;
        int k = 0;

        printf("Inside matrix_multiplication_gpuoffload %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE, 0);
        #pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(0)
        #pragma omp target device(0)
															dummyMethod1();
        #pragma omp teams distribute parallel for collapse(2) private(i,j,k)
        for(i=0;i<ROWSIZE;i++)
        {
                for(j=0;j<COLSIZE;j++)
                {
                        for(k=0;k<ROWSIZE;k++)
                        {
                                pC(i,j)+=pA(i,k)*pB(k,j);
                        }
                }
        }
															dummyMethod2();

 	int a = 0;
        int b = 0;
        int c = 0;

        printf("Inside matrix_multiplication_gpuoffload %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE, 1);
        #pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(1)
        #pragma omp target device(1)
															dummyMethod1();
        #pragma omp teams distribute parallel for collapse(2) private(a,b,c)
        for(a=0;a<ROWSIZE;a++)
        {
                for(b=0;b<COLSIZE;b++)
                {
                        for(c=0;c<ROWSIZE;c++)
                        {
                                pC(a,b)+=pA(a,c)*pB(c,b);
                        }
                }
        }
															dummyMethod2();


}

void matrix_multiplication_gpuoffload_multigpu_Async()
{
        int i = 0;
        int j = 0;
        int k = 0;

        printf("Inside matrix_multiplication_gpuoffload %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE, 0);
        #pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(0) 
        #pragma omp target device(0) 
															dummyMethod1();
        #pragma omp teams distribute parallel for collapse(2) private(i,j,k) schedule(static) 
        for(i=0;i<ROWSIZE;i++)
        {
                for(j=0;j<COLSIZE;j++)
                {
                        for(k=0;k<ROWSIZE;k++)
                        {
                                pC(i,j)+=pA(i,k)*pB(k,j);
                        }
                }
        }
															dummyMethod2();


	int a = 0;
        int b = 0;
        int c = 0;

        printf("Inside matrix_multiplication_gpuoffload %dx%d, gpuid: %d \n", ROWSIZE,COLSIZE, 1);
        #pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(1)
        #pragma omp target device(1)
															dummyMethod1();
        #pragma omp teams distribute parallel for collapse(2) private(a,b,c) schedule(static)// nowait
        for(a=0;a<ROWSIZE;a++)
        {
                for(b=0;b<COLSIZE;b++)
                {
                        for(c=0;c<ROWSIZE;c++)
                        {
                                pC(a,b)+=pA(a,c)*pB(c,b);
                        }
                }
        }
															dummyMethod2();


}






/* Compared to collapse case,
 * With split pragma performance for mm size 3k X 3k degrades by ~40 times. Adding "simd" performance worsen to ~80 times !
 **/
void matrix_multiplication_gpuoffload_split() 
{
	int i = 0;
	int j = 0;
	int k = 0;

	printf("Inside matrix_multiplication_gpuoffload_split() %dx%d \n", ROWSIZE,COLSIZE);
	#pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE])
	#pragma omp target teams distribute private(i,j,k)
	for(i=0;i<ROWSIZE;i++)
	{
		//#pragma parallel for private(i,j,k)
		for(j=0;j<COLSIZE;j++)
		{
			//#pragma omp simd 
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
	}	
}

void matrix_multiplication_gpuoffload_teams(int num_threads)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int volta_fp32_cores = 5120;
	int volta_fp64_cores = 2560;

	printf("Inside matrix_multiplication_gpuoffload_teams %dx%d: num_gpu_threads %d \n", ROWSIZE,COLSIZE, num_threads);
	#pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE])
	#pragma omp target 
	dummyMethod1();
	#pragma omp teams distribute parallel for collapse(2) private(i,j,k) num_teams(volta_fp64_cores/num_threads) thread_limit(num_threads)
	for(i=0;i<ROWSIZE;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
	}	
	dummyMethod2();
}

void matrix_multiplication_gpuoffload_schedule(int chunk)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int volta_fp32_cores = 5120;
	int volta_fp64_cores = 2560;

	printf("Inside matrix_multiplication_gpuoffload_teams %dx%d: \n", ROWSIZE,COLSIZE);
	#pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE])
	#pragma omp target 
	dummyMethod1();
	#pragma omp teams distribute parallel for collapse(2) private(i,j,k) dist_schedule(static, 1) schedule (static, 1)
	for(i=0;i<ROWSIZE;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
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