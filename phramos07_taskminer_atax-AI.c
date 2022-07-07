/**
 * atax.c: This file was adapted from PolyBench/GPU 1.0 test suite
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
#define PERCENT_DIFF_ERROR_THRESHOLD 0.5

/* Problem size. */
#define NX 8192
#define NY 8192

#define GPU_DEVICE 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *x, DATA_TYPE *A)
{
  int i, j;

  #pragma acc data copy(A[0:67117056],x[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      x[i] = i * M_PI;
      for (j = 0; j < NY; j++)
	{
	  A[i*NY + j] = ((DATA_TYPE) i*(j)) / NX;
	}
    }
			dummyMethod4();
}

void compareResults(DATA_TYPE *z, DATA_TYPE *z_outputFromGpu)
{
  int i, fail;
  fail = 0;

  #pragma acc data copy(z[0:8192],z_outputFromGpu[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i<NY; i++)
    {
      if (percentDiff(z[i], z_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD)
	{
	  fail++;
	}		
    }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

void atax_cpu(DATA_TYPE* A, DATA_TYPE* x, DATA_TYPE* y, DATA_TYPE* tmp)
{
  int i,j;
	
  #pragma acc data copy(y[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i= 0; i < NY; i++)
    {
      y[i] = 0;
    }
			dummyMethod4();
  
  #pragma acc data copy(A[0:67117056],x[0:8192],y[0:8192],tmp[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      tmp[i] = 0;
      
      for (j = 0; j < NY; j++)
	{
	  tmp[i] = tmp[i] + A[i*NY + j] * x[j];
	}
      
      for (j = 0; j < NY; j++)
	{
	  y[j] = y[j] + A[i*NY + j] * tmp[i];
	}
    }
			dummyMethod4();
}

void atax_OMP(DATA_TYPE* A, DATA_TYPE* x, DATA_TYPE* y, DATA_TYPE* tmp)
{
  int i,j;
	
  #pragma acc data copy(y[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i= 0; i < NY; i++)
    {
      y[i] = 0;
    }
			dummyMethod4();
  
  #pragma omp target device (GPU_DEVICE)
  #pragma omp target map(to: A[:NX*NY], x[:NY]) map(from: tmp[:NX]) 
			dummyMethod1();
  #pragma omp parallel for
  #pragma acc data copy(A[0:67117056],x[0:8192],tmp[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
  for (i = 0; i < NX; i++)
    {
      tmp[i] = 0;
      int j;
      for (j = 0; j < NY; j++)
	{
	  tmp[i] = tmp[i] + A[i*NY + j] * x[j];
	}
    }
			dummyMethod2();

  //Note that the Loop has been reversed
  #pragma omp target map(to: A[:NX*NY], tmp[:NX]) map(from: y[:NY]) 
			dummyMethod1();
  #pragma omp parallel for collapse(1)
  #pragma acc data copy(A[0:67117056],y[0:8192],tmp[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
  for (j = 0; j < NY; j++)
    for (i = 0; i < NX; i++){
      {
	y[j] = y[j] + A[i*NY + j] * tmp[i];
      }
    }
			dummyMethod2();
}

int main(int argc, char** argv)
{
  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* x;
  DATA_TYPE* y;
  DATA_TYPE* y_outputFromGpu;
  DATA_TYPE* tmp;

  A = (DATA_TYPE*)malloc(NX*NY*sizeof(DATA_TYPE));
  x = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  y = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  y_outputFromGpu = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  tmp = (DATA_TYPE*)malloc(NX*sizeof(DATA_TYPE));

  fprintf(stdout, "<< Matrix Transpose and Vector Multiplication >>\n");

  init_array(x, A);

  t_start = rtclock();
  atax_OMP(A, x, y_outputFromGpu, tmp);
  t_end = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);
	
  t_start = rtclock();
  atax_cpu(A, x, y, tmp);
  t_end = rtclock();
  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(y, y_outputFromGpu);

  free(A);
  free(x);
  free(y);
  free(y_outputFromGpu);
  free(tmp);

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