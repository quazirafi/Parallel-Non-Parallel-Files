/**
 * correlation.c This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *  	     Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
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

//define the error threshold for the results "not matching"
#define ERROR_THRESHOLD 1.05

#define GPU_DEVICE 1

/* Problem size */
#define M 1024
#define N 1024

#define sqrt_of_array_cell(x,j) sqrt(x[j])

#define FLOAT_N 3214212.01f
#define EPS 0.005f

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE* data)
{
  int i, j;
	
  #pragma acc data copy(data[0:1051650])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i < (M+1); i++) 
    {
      for (j=0; j< (N+1); j++) 
	{
	  data[i*(N+1) + j] = ((DATA_TYPE) i*j)/ (M+1);	
	}
    }
			dummyMethod4();
}

void correlation(DATA_TYPE* data, DATA_TYPE* mean, DATA_TYPE* stddev, DATA_TYPE* symmat)
{
  int i, j, j1, j2;	
	
  // Determine mean of column vectors of input data matrix 
  #pragma acc data copy(mean[1:1025],data[1026:1051650])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (j = 1; j < (M+1); j++)
    {
      mean[j] = 0.0;
      
      for (i = 1; i < (N+1); i++)
	{
	  mean[j] += data[i*(M+1) + j];
	}
		
      //mean[j] /= (float)FLOAT_N;
      mean[j] /= (DATA_TYPE)FLOAT_N;
    }
			dummyMethod4();

  // Determine standard deviations of column vectors of data matrix. 
  #pragma acc data copy(mean[1:1025],data[1026:1051650],stddev[1:1025])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (j = 1; j < (M+1); j++)
    {
      stddev[j] = 0.0;
      
      for (i = 1; i < (N+1); i++)
	{
	  stddev[j] += (data[i*(M+1) + j] - mean[j]) * (data[i*(M+1) + j] - mean[j]);
	}
		
      stddev[j] /= FLOAT_N;
      stddev[j] = sqrt_of_array_cell(stddev, j);
      stddev[j] = stddev[j] <= EPS ? 1.0 : stddev[j];
    }
			dummyMethod4();

  //i - threadIdx.x, j = threadIdx.y
  // Center and reduce the column vectors. 
  #pragma acc data copy(mean[1:1025],data[1026:1051650],stddev[1:1025])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 1; i < (N+1); i++)
    {
      for (j = 1; j < (M+1); j++)
	{
	  data[i*(M+1) + j] -= mean[j];
	  data[i*(M+1) + j] /= (sqrt(FLOAT_N)*stddev[j]) ;
	}
    }
			dummyMethod4();

  // Calculate the m * m correlation matrix. 
  #pragma acc data copy(data[1026:1051650],symmat[1026:1051649])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (j1 = 1; j1 < M; j1++)
    {	
      symmat[j1*(M+1) + j1] = 1.0;
      
      for (j2 = j1+1; j2 < (M+1); j2++)
	{
	  symmat[j1*(M+1) + j2] = 0.0;
	  
	  for (i = 1; i < (N+1); i++)
	    {
	      symmat[j1*(M+1) + j2] += (data[i*(M+1) + j1] * data[i*(M+1) + j2]);
	    }
	  
	  symmat[j2*(M+1) + j1] = symmat[j1*(M+1) + j2];
	}
    }
			dummyMethod4();
 
  symmat[M*(M+1) + M] = 1.0;

}


void correlation_OMP(DATA_TYPE* data, DATA_TYPE* mean, DATA_TYPE* stddev, DATA_TYPE* symmat)
{
  int i, j, k;	
	
  // Determine mean of column vectors of input data matrix 
  //Maps data once.
  #pragma omp target device (GPU_DEVICE) map (to: data[:(M+1)*(N+1)], mean[:(M+1)], stddev[:(M+1)]) map (tofrom: symmat[:(M+1)*(N+1)])
  {
					dummyMethod1();
  	  #pragma omp parallel for
	  #pragma acc data copy(data[1026:1051650],mean[1:1025])
	  #pragma acc kernels
	  #pragma acc loop independent
	  for (j = 1; j < (M+1); j++)
	    {
	      mean[j] = 0.0;
	      int i;
	      for (i = 1; i < (N+1); i++)
		{
		  mean[j] += data[i*(M+1) + j];
		}  
	      mean[j] /= (DATA_TYPE)FLOAT_N;
	    }
					dummyMethod2();

	  // Determine standard deviations of column vectors of data matrix. 
					dummyMethod1();
	  #pragma omp parallel for
	  #pragma acc data copy(data[1026:1051650],mean[1:1025],stddev[1:1025])
	  #pragma acc kernels
	  #pragma acc loop independent
	  for (j = 1; j < (M+1); j++)
	    {
	      stddev[j] = 0.0;
	      int i;
	      for (i = 1; i < (N+1); i++)
		{
		  stddev[j] += (data[i*(M+1) + j] - mean[j]) * (data[i*(M+1) + j] - mean[j]);
		}
		
	      stddev[j] /= FLOAT_N;
	      stddev[j] = sqrt(stddev[j]);
	      if(stddev[j] <=EPS)
		{
		  stddev[j] = 1.0;
		}
	    }
					dummyMethod2();

	  //i - threadIdx.x, j = threadIdx.y
	  // Center and reduce the column vectors. 
					dummyMethod1();
	  #pragma omp parallel for collapse(2)
	  #pragma acc data copy(data[1026:1051650],mean[1:1025],stddev[1:1025])
	  #pragma acc kernels
	  #pragma acc loop independent
	  for (i = 1; i < (N+1); i++)
	    {
	      for (j = 1; j < (M+1); j++)
		{
		  data[i*(M+1) + j] -= mean[j];
		  data[i*(M+1) + j] /= (sqrt(FLOAT_N)*stddev[j]) ;
		}
	    }
					dummyMethod2();

	  // Calculate the m * m correlation matrix. 
					dummyMethod1();
	  #pragma omp parallel for
	  #pragma acc data copy(data[1026:1051650],symmat[1026:1051649])
	  #pragma acc kernels
	  #pragma acc loop independent
	  for (k = 1; k < M; k++)
	  {	
	      symmat[k*(M+1) + k] = 1.0;
	      int j;
	      for (j = k+1; j < (M+1); j++)
		{
		  symmat[k*(M+1) + j] = 0.0;
		  int i;
		  for (i = 1; i < (N+1); i++)
		    {
		      symmat[k*(M+1) + j] += (data[i*(M+1) + k] * data[i*(M+1) + j]);
		    }	  
		  symmat[j*(M+1) + k] = symmat[k*(M+1) + j];
		}
	  }
					dummyMethod2();
  }
  
  symmat[M*(M+1) + M] = 1.0;

}

void compareResults(DATA_TYPE* symmat, DATA_TYPE* symmat_outputFromGpu)
{
  int i,j,fail;
  fail = 0;

  #pragma acc data copy(symmat[1026:1051650],symmat_outputFromGpu[1026:1051650])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=1; i < (M+1); i++)
    {
      for (j=1; j < (N+1); j++)
	{
	  if (percentDiff(symmat[i*(N+1) + j], symmat_outputFromGpu[i*(N+1) + j]) > ERROR_THRESHOLD)
	    {
	      fail++;
	      //printf("i: %d j: %d\n1: %f 2: %f\n", i, j, symmat[i*N + j], symmat_GPU[i*N + j]);		
	    }
	}
    }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", ERROR_THRESHOLD, fail);
}

int main()
{
  double t_start, t_end;

  DATA_TYPE* data;
  DATA_TYPE* mean;
  DATA_TYPE* stddev;
  DATA_TYPE* symmat;
  DATA_TYPE* symmat_GPU;

  data = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE));
  mean = (DATA_TYPE*)malloc((M+1)*sizeof(DATA_TYPE));
  stddev = (DATA_TYPE*)malloc((M+1)*sizeof(DATA_TYPE));
  symmat = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE));
  symmat_GPU = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE));

  fprintf(stdout, "<< Correlation Computation >>\n");

  init_arrays(data);

  t_start = rtclock();
  correlation_OMP(data, mean, stddev, symmat_GPU);
  t_end = rtclock();

  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

  t_start = rtclock();
  correlation(data, mean, stddev, symmat);
  t_end = rtclock();

  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);
    
  compareResults(symmat, symmat_GPU);

  free(data);
  free(mean);
  free(stddev);
  free(symmat);
  free(symmat_GPU);

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