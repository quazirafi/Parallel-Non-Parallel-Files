/**
 * bicg.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//include <omp.h>

#include "../../common/polybenchUtilFuncts.h"

//Error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.7

/* Problem size. */
#define NX 8192
#define NY 8192

#define GPU_DEVICE 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *A, DATA_TYPE *p, DATA_TYPE *r)
{
  int i, j;

  #pragma acc data copy(r[0:8192],A[0:67117056])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      r[i] = i * M_PI;
      for (j = 0; j < NY; j++)
	{
	  A[i*NY + j] = ((DATA_TYPE) i*j) / NX;
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(p[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NY; i++)
    {
      p[i] = i * M_PI;
    }
			dummyMethod4();
}

void compareResults(DATA_TYPE* s, DATA_TYPE* s_outputFromGpu, DATA_TYPE* q, DATA_TYPE* q_outputFromGpu)
{
  int i,fail;
  fail = 0;

  // Compare s with s_cuda
  #pragma acc data copy(q[0:8192],q_outputFromGpu[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i<NX; i++)
    {
      if (percentDiff(q[i], q_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD)
	{
	  fail++;
	}
    }
			dummyMethod4();
  
  #pragma acc data copy(s[0:8192],s_outputFromGpu[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i<NY; i++)
    {
      if (percentDiff(s[i], s_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD)
	{
	  fail++;
	}		
    }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}


void bicg_cpu(DATA_TYPE* A, DATA_TYPE* r, DATA_TYPE* s, DATA_TYPE* p, DATA_TYPE* q)
{
  int i,j;
	
  #pragma acc data copy(s[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NY; i++)
    {
      s[i] = 0.0;
    }
			dummyMethod4();
  
  #pragma acc data copy(s[0:8192],r[0:8192],A[0:67117056],q[0:8192],p[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      q[i] = 0.0;
      for (j = 0; j < NY; j++)
	{
	  s[j] = s[j] + r[i] * A[i*NY + j];
	  q[i] = q[i] + A[i*NY + j] * p[j];
	}
    }
			dummyMethod4();
}

void bicg_OMP(DATA_TYPE* A, DATA_TYPE* r, DATA_TYPE* s, DATA_TYPE* p, DATA_TYPE* q)
{
  int i, j;
	
  #pragma acc data copy(s[0:8192])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < NY; i++)
    {
      s[i] = 0.0;
    }
			dummyMethod4();

  #pragma omp target device (GPU_DEVICE) map(to: A[:NX*NY], p[:NY], r[:NX]) map(tofrom: s[:NY], q[:NX])
  {
					dummyMethod1();
	  #pragma omp parallel for collapse(1)
	  #pragma acc data copy(A[0:67117056],r[0:8192],s[0:8192])
	  #pragma acc kernels
	  #pragma acc loop independent
	  for (j = 0; j < NY; j++)
	  {
		for (i = 0; i < NX; i++)
	  	{
	    		s[j] = s[j] + r[i] * A[i*NY + j];
	  	}
	  }
					dummyMethod2();

							dummyMethod1();
	   #pragma omp parallel for collapse(1)
	   #pragma acc data copy(A[0:67117056],p[0:8192],q[0:8192])
	   #pragma acc kernels
	   #pragma acc loop independent
	   for (i = 0; i < NX; i++)
	   {
		q[i] = 0.0;
		for (j = 0; j < NY; j++)
	  	{
	    		q[i] = q[i] + A[i*NY + j] * p[j];
	  	}
	   } 
							dummyMethod2();
   }
}


int main(int argc, char** argv)
{
  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* r;
  DATA_TYPE* s;
  DATA_TYPE* p;
  DATA_TYPE* q;
  DATA_TYPE* s_GPU;
  DATA_TYPE* q_GPU;
 	
  A = (DATA_TYPE*)malloc(NX*NY*sizeof(DATA_TYPE));
  r = (DATA_TYPE*)malloc(NX*sizeof(DATA_TYPE));
  s = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  p = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  q = (DATA_TYPE*)malloc(NX*sizeof(DATA_TYPE));
  s_GPU = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  q_GPU = (DATA_TYPE*)malloc(NX*sizeof(DATA_TYPE));

  fprintf(stdout, "<< BiCG Sub Kernel of BiCGStab Linear Solver >>\n");

  init_array(A, p, r);

  t_start = rtclock();
  bicg_OMP(A, r, s_GPU, p, q_GPU);
  t_end = rtclock();

  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

  t_start = rtclock();
  bicg_cpu(A, r, s, p, q);
  t_end = rtclock();

  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(s, s_GPU, q, q_GPU);

  free(A);
  free(r);
  free(s);
  free(p);
  free(q);
  free(s_GPU);
  free(q_GPU);

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