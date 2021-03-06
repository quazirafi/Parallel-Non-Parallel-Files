/**
 * gramschmidt.c: This file was adapted from PolyBench/GPU 1.0 test
 * suite to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU 
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br> 
*/

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//include <omp.h>

#include "../../common/polybenchUtilFuncts.h"

//define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

/* Problem size */
#define M 512
#define N 512

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

#define GPU_DEVICE 1

void gramschmidt(DATA_TYPE* A, DATA_TYPE* R, DATA_TYPE* Q)
{
  int i,j,k;
  DATA_TYPE nrm;
  #pragma acc data copy(R[0:262656],Q[0:262656],A[0:262656])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (k = 0; k < N; k++)
    {
      nrm = 0;
      for (i = 0; i < M; i++)
	{
	  nrm += A[i*N + k] * A[i*N + k];
	}
      
      R[k*N + k] = sqrt(nrm);
      for (i = 0; i < M; i++)
	{
	  Q[i*N + k] = A[i*N + k] / R[k*N + k];
	}
      
      for (j = k + 1; j < N; j++)
	{
	  R[k*N + j] = 0;
	  for (i = 0; i < M; i++)
	    {
	      R[k*N + j] += Q[i*N + k] * A[i*N + j];
	    }
	  for (i = 0; i < M; i++)
	    {
	      A[i*N + j] = A[i*N + j] - Q[i*N + k] * R[k*N + j];
	    }
	}
    }
			dummyMethod4();
}

void gramschmidt_OMP(DATA_TYPE* A, DATA_TYPE* R, DATA_TYPE* Q)
{
  int i,j,k;
  DATA_TYPE nrm;
	
  #pragma acc data copy(A[0:262656],R[0:262656],Q[0:262656])
  #pragma acc kernels
  #pragma acc loop independent
  for (k = 0; k < N; k++)
    {
      //CPU
      nrm = 0;
      for (i = 0; i < M; i++)
	{
	  nrm += A[i*N + k] * A[i*N + k];
	}
      R[k*N + k] = sqrt(nrm); 
      
      #pragma omp target device (GPU_DEVICE)
      #pragma omp target map(to: A[:M*N], R[:M*N]) map(from: Q[:M*N])
											dummyMethod1();
      #pragma omp parallel for 
      for (i = 0; i < M; i++)
	{
	  Q[i*N + k] = A[i*N + k] / R[k*N + k];
	}
											dummyMethod2();
      
      #pragma omp target map(to: R[:M*N], Q[:M*N]) map(tofrom: A[:M*N])
											dummyMethod1();
      #pragma omp parallel for
      for (j = k + 1; j < N; j++)
	{
	  R[k*N + j] = 0;
	  for (i = 0; i < M; i++)
	    {
	      R[k*N + j] += Q[i*N + k] * A[i*N + j];
	    }
	  for (i = 0; i < M; i++)
	    {
	      A[i*N + j] = A[i*N + j] - Q[i*N + k] * R[k*N + j];
	    }
	}
											dummyMethod2();
    }
}


void init_array(DATA_TYPE* A, DATA_TYPE* A2)
{
  int i, j;

  #pragma acc data copy(A[0:262656],A2[0:262656])
  #pragma acc kernels
  #pragma acc loop independent
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < N; j++)
	{
	  A[i*N + j] = ((DATA_TYPE) (i+1)*(j+1)) / (M+1);
	  A2[i*N + j] = A[i*N + j];
	}
    }
}


void compareResults(DATA_TYPE* A, DATA_TYPE* A_outputFromGpu)
{
  int i, j, fail;
  fail = 0;

  #pragma acc data copy(A[0:262656],A_outputFromGpu[0:262656])
  #pragma acc kernels
  #pragma acc loop independent
  for (i=0; i < M; i++) 
    {
      for (j=0; j < N; j++) 
	{
	  if (percentDiff(A[i*N + j], A_outputFromGpu[i*N + j]) > PERCENT_DIFF_ERROR_THRESHOLD) 
	    {				
	      fail++;
	      //printf("i: %d j: %d \n1: %f\n 2: %f\n", i, j, A[i*N + j], A_outputFromGpu[i*N + j]);
	    }
	}
    }
	
  // Print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

int main(int argc, char *argv[])
{
  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* A_outputFromGpu;
  DATA_TYPE* R;
  DATA_TYPE* Q;
	
  A = (DATA_TYPE*)malloc(M*N*sizeof(DATA_TYPE));
  A_outputFromGpu = (DATA_TYPE*)malloc(M*N*sizeof(DATA_TYPE));
  R = (DATA_TYPE*)malloc(M*N*sizeof(DATA_TYPE));  
  Q = (DATA_TYPE*)malloc(M*N*sizeof(DATA_TYPE));  
	
  fprintf(stdout, "<< Gram-Schmidt decomposition >>\n");

  init_array(A, A_outputFromGpu );

  t_start = rtclock();
  gramschmidt_OMP(A_outputFromGpu, R, Q);
  t_end = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);
	
  t_start = rtclock();
  gramschmidt(A, R, Q);
  t_end = rtclock();
  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);
	
  compareResults(A, A_outputFromGpu);
	
  free(A);
  free(A_outputFromGpu);
  free(R);
  free(Q);  

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