/**
 * 2mm.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU 
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *	     Luís Felipe Mattos <ra107822@students.ic.unicamp.br> 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//include <omp.h>

#include "../../common/polybenchUtilFuncts.h"

//define the error threshold for the results "not matching"
#define ERROR_THRESHOLD 0.05

#define GPU_DEVICE 1

/* Problem size. */
# define NI 1024
# define NJ 1024
# define NK 1024
# define NL 1024

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE* A, DATA_TYPE* B, DATA_TYPE* C, DATA_TYPE* D)
{
  int i, j;

  #pragma acc data copy(A[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NK; j++)
	{
	  A[i*NI + j] = ((DATA_TYPE) i*j) / NI;
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(B[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NK; i++)
    {
      for (j = 0; j < NJ; j++)
	{
	  B[i*NK + j] = ((DATA_TYPE) i*(j+1)) / NJ;
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(C[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NL; i++)
    {
      for (j = 0; j < NJ; j++)
	{
	  C[i*NL + j] = ((DATA_TYPE) i*(j+3)) / NL;
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(D[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NL; j++)
	{
	  D[i*NL + j] = ((DATA_TYPE) i*(j+2)) / NK;	
	}
    }
			dummyMethod4();
}

void compareResults(DATA_TYPE *E, DATA_TYPE *E_GPU)
{
  int i,j,fail;
  fail = 0;

  #pragma acc data copy(E[0:1049600],E_GPU[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i < NL; i++)
    {
      for (j=0; j < NI; j++)
	{
	  if (percentDiff(E[i*NI + j], E_GPU[i*NI + j]) > ERROR_THRESHOLD)
	    {
	      fail++;
	    }
	}
    }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", ERROR_THRESHOLD, fail);
}

void mm2_cpu(DATA_TYPE* A, DATA_TYPE* B, DATA_TYPE* C, DATA_TYPE* D, DATA_TYPE* E)
{
  int i, j, k;

  #pragma acc data copy(A[0:1049600],B[0:1049600],C[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NJ; j++)
	{
	  C[i*NJ + j] = 0.0;
	  for (k = 0; k < NK; ++k)
	    {
	      C[i*NJ + j] += A[i*NK + k] * B[k*NJ + j];
	    }
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(C[0:1049600],D[0:1049600],E[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NL; j++)
	{
	  E[i*NL + j] = 0.0;
	  for (k = 0; k < NJ; ++k)
	    {
	      E[i*NL + j] += C[i*NJ + k] * D[k*NL + j];
	    }
	}
    }
			dummyMethod4();
}

void mm2_OMP(DATA_TYPE* A, DATA_TYPE* B, DATA_TYPE* C, DATA_TYPE* D, DATA_TYPE* E)
{
  int i, j;

  #pragma omp target device (GPU_DEVICE)
  #pragma omp target map(to: A[:NI*NK], B[:NK*NJ]) map(from: C[:NI*NJ])
			dummyMethod1();
  #pragma omp parallel for
  #pragma acc data copy(A[0:1049600],B[0:1049600],C[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NJ; j++)
	{
	  C[i*NJ + j] = 0.0;
	  int k;
	  for (k = 0; k < NK; ++k)
	    {
	      C[i*NJ + j] += A[i*NK + k] * B[k*NJ + j];
	    }
	}
    }
			dummyMethod2();
	
  #pragma omp target map(to: C[:NI*NJ], D[:NJ*NL]) map(from: E[:NI*NL])
			dummyMethod1();
  #pragma omp parallel for
  #pragma acc data copy(C[0:1049600],D[0:1049600],E[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
  for (i = 0; i < NI; i++)
    {
      for (j = 0; j < NL; j++)
	{
	  E[i*NL + j] = 0.0;
	  int k;
	  for (k = 0; k < NJ; ++k)
	    {
	      E[i*NL + j] += C[i*NJ + k] * D[k*NL + j];
	    }
	}
    }
			dummyMethod2();
}

int main(int argc, char** argv)
{
  double t_start, t_end, t_start_GPU, t_end_GPU;

  DATA_TYPE* C;
  DATA_TYPE* A;
  DATA_TYPE* B;
  DATA_TYPE* D;
  DATA_TYPE* E;
  DATA_TYPE* E_GPU;

  C = (DATA_TYPE*)malloc(NI*NJ*sizeof(DATA_TYPE));
  A = (DATA_TYPE*)malloc(NI*NK*sizeof(DATA_TYPE));
  B = (DATA_TYPE*)malloc(NK*NJ*sizeof(DATA_TYPE));
  D = (DATA_TYPE*)malloc(NJ*NL*sizeof(DATA_TYPE));
  E = (DATA_TYPE*)malloc(NI*NL*sizeof(DATA_TYPE));
  E_GPU = (DATA_TYPE*)malloc(NI*NL*sizeof(DATA_TYPE));

  fprintf(stdout, "<< Linear Algebra: 2 Matrix Multiplications (D=A.B; E=C.D) >>\n");

  init_array(A, B, C, D);

  t_start_GPU = rtclock();
  mm2_OMP(A, B, C, D, E_GPU);
  t_end_GPU = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end_GPU - t_start_GPU);	

  t_start = rtclock();
  mm2_cpu(A, B, C, D, E);
  t_end = rtclock();
  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(E, E_GPU);

  free(C);
  free(A);
  free(B);
  free(D);
  free(E);
  free(E_GPU);

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