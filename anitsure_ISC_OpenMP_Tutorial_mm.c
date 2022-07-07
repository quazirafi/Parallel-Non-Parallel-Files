#include <unistd.h>
#include "mm.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef MM_GPU_ATS
	#include<cuda_runtime.h>
#endif

void triad_1loop()
{
	size_t j = 0;
	printf("Inside triad_1loop \n");
dummyMethod1();
	#pragma omp parallel for
    for (j=0; j<array_size; j++)
	{
	//printf("Inside triad_1loop \n");
dummyMethod2();
        a[j] = b[j]+scalar*c[j];
	}
}
/*
void matrix_multiplication()
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	printf("Inside matrix_multiplication %dx%d \n", ROWSIZE,COLSIZE);
	#pragma omp parallel for collapse(2) private(i,j,k) shared(pA,pB,pC)
	for(i=0;i<ROWSIZE;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
//				printf("pC(%d,%d) = pA(%d,%d)*pB(%d,%d) \n",i,j, i, k, k, j);
			}
			//printf("pC: %f = pA: * pB: \n",pC(i,j)); 
		}
	}	
}
*/
void matrix_multiplication(int np, int pid, double *recA, double *recC)
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	printf("Inside MPI matrix_multiplication %dx%d : %d \n", ROWSIZE/np,COLSIZE, pid);
	dummyMethod1();
	#pragma omp parallel for collapse(2) private(i,j,k) shared(recA,pB,recC)
	for(i=0;i<ROWSIZE/np;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<COLSIZE;k++)
			{
				recC(i,j)+=recA(i,k)*pB(k,j);

//				printf("recC(%d,%d) = recA(%d,%d)*pB(%d,%d) \n",i,j, i, k, k, j);
//				printf("proc (%d) : recA(%d,%d): %f \n",pid, i,k, recA(i,k) );
			}
			//printf("pC: %f = pA: * pB: \n",pC(i,j)); 
		}
	}	
	dummyMethod2();
}


void init_arrays_matmul_mpi(int np, int pid)
{
	int j = 0;
	
	printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);

	pB = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

	recA = (double*) malloc(sizeof(double) * ROWSIZE/np * COLSIZE);
    recC = (double*) malloc(sizeof(double) * ROWSIZE/np * COLSIZE);

	if(pid == 0)
	{
		pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
		pC = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

			dummyMethod1();
		#pragma omp parallel for
		for (j=0; j<ROWSIZE*COLSIZE; j++) 
		{
       		pA[j] = 2.0;
	        pB[j] = 6.0;
    	    pC[j] = 0.0;
    	}
			dummyMethod2();
	}
	
	printf (" process %d create rec buffer \n " , pid ) ;
	
	dummyMethod3();
	for (int i=0; i< ROWSIZE/np * COLSIZE; i++)
	{
		recA[i] = 0;
		recC[i] = 0;
	}
	dummyMethod4();
}

void init_arrays_matmul()
{
	int j = 0;
	
	printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);

	pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pB = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pC = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

	dummyMethod1();
	#pragma omp parallel for
	for (j=0; j<ROWSIZE*COLSIZE; j++) 
	{
        pA[j] = 2.0;
        pB[j] = 6.0;
        pC[j] = 0.0;
    }
	dummyMethod2();
}

#ifdef MM_GPU_ATS
void init_arrays_matmul_ats()
{
	int j = 0;
	
	omp_set_default_device(0);

	printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);

	pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pB = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pC = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);


	cudaMemPrefetchAsync(pA, ROWSIZE*COLSIZE*sizeof(double),0,0);
	cudaMemPrefetchAsync(pB, ROWSIZE*COLSIZE*sizeof(double),0,0);
	cudaMemPrefetchAsync(pC, ROWSIZE*COLSIZE*sizeof(double),0,0);
	cudaDeviceSynchronize();

	#pragma omp parallel for
	for (j=0; j<ROWSIZE*COLSIZE; j++) 
	{
        pA[j] = 2.0;
        pB[j] = 6.0;
        pC[j] = 0.0;
    }
}
#endif
void print_matrix(double *pC)
{
	int i = 0;
	int j = 0;
	
	printf("######################### 2D printing ########################################### \n");

	dummyMethod3();
	for(i=0; i<ROWSIZE; i++)
	{
		for(j=0; j<COLSIZE; j++)
		{
			printf("%f ", pC(i,j));
		}
		printf("\n");
	}
	dummyMethod4();
	
	printf("######################### 1D printing ########################################### \n");

	dummyMethod3();
	for(i=0; i<ROWSIZE*COLSIZE; i++)
	{
		printf("%f ", pC[i]);
	}
	dummyMethod4();
	printf("\n");
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