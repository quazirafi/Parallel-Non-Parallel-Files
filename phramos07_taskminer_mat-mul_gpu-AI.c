/*
   This program performs matrix multiplication on the GPU with 
   dynamically allocated matrices.
    
    Author: Gleison Souza Diniz Mendonça 
    Date: 04-01-2015
    version 2.0
    
    Run:
    ipmacc mat-mul_gpu.c -o mat
    ./mat matrix-size
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../common/mgbenchUtilFunctions.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 1000
#define GPU_DEVICE 0
#define PERCENT_DIFF_ERROR_THRESHOLD 0.01

// Initialize matrices.
void init(float *a, float *b, float *c_cpu, float *c_gpu) 
{
    int i, j;
    #pragma acc data copy(c_cpu[0:1001000],c_gpu[0:1001000],b[0:1001000],a[0:1001000])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for (i = 0; i < SIZE; ++i)
    {
	for (j = 0; j < SIZE; ++j)
	{
    	    a[i * SIZE + j] = (float)i + j % 100;
	    b[i * SIZE + j] = (float)i + j % 100;
	    c_cpu[i * SIZE + j] = 0.0f;
	    c_gpu[i * SIZE + j] = 0.0f;
	}
    }
							dummyMethod4();
}

/// matrix multiplication algorithm GPU
/// s = size of matrix
void mul_GPU(float *a, float *b, float *c) 
{
    int i, j, k;

    float sum = 0.0;

    #pragma omp target device (GPU_DEVICE)
    #pragma omp target map(to: a[0:SIZE*SIZE], b[0:SIZE*SIZE]) map(tofrom: c[0:SIZE*SIZE])
    {
	dummyMethod1();
	#pragma omp parallel for collapse(2)
	#pragma acc data copy(a[0:1001000],b[0:1001000],c[0:1001000])
	#pragma acc kernels
	#pragma acc loop independent
	for (i = 0; i < SIZE; ++i) 
	{
	    for (j = 0; j < SIZE; ++j) 
	    {
		sum = 0.0;
		for (k = 0; k < SIZE; ++k) 
		{
	    	    sum = sum + a[i * SIZE + k] * b[k * SIZE + j];
		}
		c[i * SIZE + j] = sum;
	    }												
	}					
	dummyMethod2();
    }			

}

void mul_CPU(float *a, float *b, float *c)
{

    int i,j,k;
    float sum = 0.0;

    #pragma acc data copy(a[0:1001000],b[0:1001000],c[0:1001000])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for (i = 0; i < SIZE; ++i) 
    {
	for (j = 0; j < SIZE; ++j) 
	{
	    sum = 0.0;
	    for (k = 0; k < SIZE; ++k) 
	    {
		sum = sum + a[i * SIZE + k] * b[k * SIZE + j];
	    }
	    c[i * SIZE + j] = sum;
        }
    }
							dummyMethod4();
}


void compareResults(float *b_cpu, float *b_gpu)
{
  int i, j, fail;
  fail = 0;
	
  #pragma acc data copy(b_cpu[0:1001000],b_gpu[0:1001000])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i < SIZE; i++) 
  {
      for (j=0; j < SIZE; j++) 
      {
	  if (percentDiff(b_cpu[i*SIZE + j], b_gpu[i*SIZE + j]) > PERCENT_DIFF_ERROR_THRESHOLD) 
	  {
	      fail++;
	  }
      }
   }
			dummyMethod4();
	
  // Print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}


int main(int argc, char *argv[]) {
   
    double t_start, t_end;
    float *a, *b, *c_cpu, *c_gpu;
   
    a = (float *) malloc(sizeof(float) * SIZE * SIZE);
    b = (float *) malloc(sizeof(float) * SIZE * SIZE);
    c_cpu = (float *) malloc(sizeof(float) * SIZE * SIZE);
    c_gpu = (float *) malloc(sizeof(float) * SIZE * SIZE);

    init(a, b, c_cpu, c_gpu);

    fprintf(stdout, "<< Matrix Multiplication >>\n");

    t_start = rtclock();
    mul_GPU(a, b, c_gpu);
    t_end = rtclock();
    fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);	

    t_start = rtclock();
    mul_CPU(a, b, c_cpu);
    t_end = rtclock();
    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);	

    compareResults(c_cpu, c_gpu);
 
    free(a);
    free(b);
    free(c_cpu);
    free(c_gpu);

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