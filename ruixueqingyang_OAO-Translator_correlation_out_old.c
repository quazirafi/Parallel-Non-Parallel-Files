#include <malloc.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
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
#include "omp.h"

//polybenchUtilFuncts.h
//Scott Grauer-Gray (sgrauerg@gmail.com)
//Functions used across hmpp codes

#ifndef POLYBENCH_UTIL_FUNCTS_H
#define POLYBENCH_UTIL_FUNCTS_H

//define a small float value
#define SMALL_FLOAT_VAL 0.00000001f

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}

float absVal(float a)
{
	if(a < 0)
	{
		return (a * -1);
	}
   	else
	{ 
		return a;
	}
}

float percentDiff(double val1, double val2)
{
	if ((absVal(val1) < 0.01) && (absVal(val2) < 0.01))
	{
		return 0.0f;
	}

	else
	{
    		return 100.0f * (absVal(absVal(val1 - val2) / absVal(val1 + SMALL_FLOAT_VAL)));
	}
} 

#endif //POLYBENCH_UTIL_FUNCTS_H

int main();
//define the error threshold for the results "not matching"
#define ERROR_THRESHOLD 1.05

#define GPU_DEVICE 1

/* Problem size */
#define M 2048
#define N 2048

#define sqrt_of_array_cell(x,j) sqrt(x[j])

#define FLOAT_N 3214212.01f
#define EPS 0.005f

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE* data, int data_LEN_)
{
  int i, j;
	
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

void correlation(DATA_TYPE* data, int data_LEN_, DATA_TYPE* mean, int mean_LEN_, DATA_TYPE* stddev, int stddev_LEN_, DATA_TYPE* symmat, int symmat_LEN_)
{
  int i, j, j1, j2;	
	
  // Determine mean of column vectors of input data matrix 
			dummyMethod3();
  for (j = 1; j < (M+1); j++)
    {
      mean[j] = 0.0;
      
      for (i = 1; i < (N+1); i++)
	{
	  mean[j] += data[i*(M+1) + j];
	}
		
      mean[j] /= (DATA_TYPE)FLOAT_N;
    }
			dummyMethod4();

  // Determine standard deviations of column vectors of data matrix. 
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


void GPU__correlation(DATA_TYPE* data, int data_LEN_, DATA_TYPE* mean, int mean_LEN_, DATA_TYPE* stddev, int stddev_LEN_, DATA_TYPE* symmat, int symmat_LEN_)
{
  int i, j, k;	
	
  // Determine mean of column vectors of input data matrix 
			dummyMethod1();
  #pragma omp target teams distribute parallel for 
  for (j = 1; j < (M+1); j++)
    {
      mean[j] = 0.0;
      for (i = 1; i < (N+1); i++)
	{
	  mean[j] += data[i*(M+1) + j];
	}  
      mean[j] /= (DATA_TYPE)FLOAT_N;
    }
			dummyMethod2();

  // Determine standard deviations of column vectors of data matrix. 
  
  #pragma omp target update from( mean[:mean_LEN_] )
			dummyMethod3();
  for (j = 1; j < (M+1); j++)
    {
      stddev[j] = 0.0;
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
			dummyMethod4();

  // Center and reduce the column vectors. 
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
  #pragma omp target update to( data[:data_LEN_] )
  
			dummyMethod1();
  #pragma omp target teams distribute parallel for  collapse(1)
  for (k = 1; k < M; k++)
    {	
      symmat[k*(M+1) + k] = 1.0;
      for (j = k+1; j < (M+1); j++)
	{
	  symmat[k*(M+1) + j] = 0.0;
	  for (i = 1; i < (N+1); i++)
	    {
	      symmat[k*(M+1) + j] += (data[i*(M+1) + k] * data[i*(M+1) + j]);
	    }	  
	  symmat[j*(M+1) + k] = symmat[k*(M+1) + j];
	}
    }
			dummyMethod2();
    #pragma omp target update from( symmat[:symmat_LEN_] )
    
  
  symmat[M*(M+1) + M] = 1.0;
  return;
}

void compareResults(DATA_TYPE* symmat, int symmat_LEN_, DATA_TYPE* symmat_outputFromGpu, int symmat_outputFromGpu_LEN_)
{
  int i,j,fail;
  fail = 0;

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

  DATA_TYPE* data; int data_LEN_;
  DATA_TYPE* mean; int mean_LEN_;
  DATA_TYPE* stddev; int stddev_LEN_;
  DATA_TYPE* symmat; int symmat_LEN_;
  DATA_TYPE* symmat_GPU; int symmat_GPU_LEN_;

  data = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE)); data_LEN_ = malloc_usable_size( data ) / sizeof( DATA_TYPE );
  mean = (DATA_TYPE*)malloc((M+1)*sizeof(DATA_TYPE)); mean_LEN_ = malloc_usable_size( mean ) / sizeof( DATA_TYPE );
  stddev = (DATA_TYPE*)malloc((M+1)*sizeof(DATA_TYPE)); stddev_LEN_ = malloc_usable_size( stddev ) / sizeof( DATA_TYPE );
  symmat = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE)); symmat_LEN_ = malloc_usable_size( symmat ) / sizeof( DATA_TYPE );
  symmat_GPU = (DATA_TYPE*)malloc((M+1)*(N+1)*sizeof(DATA_TYPE)); symmat_GPU_LEN_ = malloc_usable_size( symmat_GPU ) / sizeof( DATA_TYPE );

  printf("<< Correlation Computation >>\n");

  
  #pragma omp target enter data map( alloc: data[:data_LEN_] )
  init_arrays(data, data_LEN_);

  t_start = rtclock();
  
  #pragma omp target enter data map( to: mean[:mean_LEN_], symmat_GPU[:symmat_GPU_LEN_] )
  
  #pragma omp target update to( data[:data_LEN_] )
  GPU__correlation(data, data_LEN_, mean, mean_LEN_, stddev, stddev_LEN_, symmat_GPU, symmat_GPU_LEN_);
  t_end = rtclock();

  printf( "GPU Runtime: %0.6lfs\n", t_end - t_start);

  init_arrays(data, data_LEN_);

  t_start = rtclock();
  correlation(data, data_LEN_, mean, mean_LEN_, stddev, stddev_LEN_, symmat, symmat_LEN_);
  t_end = rtclock();

  printf("CPU Runtime: %0.6lfs\n", t_end - t_start);
    
  compareResults(symmat, symmat_LEN_, symmat_GPU, symmat_GPU_LEN_);

  
  #pragma omp target exit data map( delete: data[:data_LEN_] )
  free(data);
  
  #pragma omp target exit data map( delete: mean[:mean_LEN_] )
  free(mean);
  free(stddev);
  free(symmat);
  
  #pragma omp target exit data map( delete: symmat_GPU[:symmat_GPU_LEN_] )
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