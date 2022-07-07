/**
 * syrk.c: This file was adapted from PolyBench/GPU 1.0 test suite
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
#include "../../common/polybenchUtilFuncts.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//define the error threshold for the results "not matching"
#define ERROR_THRESHOLD 0.05
#define GPU_DEVICE 1

/* Problem size */
#define N 1024
#define M 1024

/* Declared constant values for alpha and beta */
/* (same as values in PolyBench 2.0) */
#define alpha 12435
#define beta 4546

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE* A, DATA_TYPE* C, DATA_TYPE* D) {
  int i, j;
	
  #pragma acc data copy(D[0:1049600],C[0:1049600],A[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      A[i*M + j] = ((DATA_TYPE) i*j) / N;
    }
    for (j = 0; j < M; j++) {
      C[i*M + j] = ((DATA_TYPE) i*j + 2) / N;
      D[i*M + j] = ((DATA_TYPE) i*j + 2) / N;
    }
  }
			dummyMethod4();
}

void compareResults(DATA_TYPE* C, DATA_TYPE* D) {
  int i,j,fail;
  fail = 0;

  // Compare C with D
  #pragma acc data copy(C[0:1049600],D[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i<N; i++) {
    for (j=0; j<M; j++)	{
      if (percentDiff(C[i*M + j], D[i*M + j]) > ERROR_THRESHOLD) {
	fail++;
      }
    }
  }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", ERROR_THRESHOLD, fail);
}

void syrk(DATA_TYPE* A, DATA_TYPE* C) {
  int i, j, k;
	
  #pragma acc data copy(C[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      C[i*M + j] *= beta;
    }
  }
			dummyMethod4();
	
  #pragma acc data copy(C[0:1049600],A[0:1049600])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      for (k = 0; k < M; k++) {
	C[i*N + j] += alpha * A[i*M + k] * A[j*M + k];
      }
    }
  }
			dummyMethod4();
}

void syrkGPU(DATA_TYPE* A, DATA_TYPE* D) {
  int i, j;
  double t_start, t_end;

  t_start = rtclock();

  #pragma omp target  device (GPU_DEVICE)
  #pragma omp target map(to: A[:N*M]) map(tofrom: D[:N*M])
  {
							dummyMethod1();
    #pragma omp parallel for
    #pragma acc data copy(D[0:1049600])
    #pragma acc kernels
    #pragma acc loop independent
    for (i = 0; i < N; i++) {
      for (j = 0; j < M; j++) {
	D[i * M + j] *= beta;
      }
    }
							dummyMethod2();
    
							dummyMethod1();
    #pragma omp parallel for collapse(2)
    #pragma acc data copy(A[0:1049600],D[0:1049600])
    #pragma acc kernels
    #pragma acc loop independent
    for (i = 0; i < N; i++) {
      for (j = 0; j < M; j++) {
	int k;		
	for(k=0; k< M; k++) {
	  D[i * M + j] += alpha * A[i * M + k] * A[j * M + k];
	}
      }
    }
							dummyMethod2();
  }
  
  t_end = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

}


int main() {
  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* C;
  DATA_TYPE* D;

  A = (DATA_TYPE*)malloc(N*M*sizeof(DATA_TYPE));
  C = (DATA_TYPE*)malloc(N*M*sizeof(DATA_TYPE));
  D = (DATA_TYPE*)malloc(N*M*sizeof(DATA_TYPE));

  fprintf(stdout, "<< Symmetric rank-k operations >>\n");

  init_arrays(A, C, D);	
  syrkGPU(A, D);

  t_start = rtclock();
  syrk(A, C);
  t_end = rtclock();
  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(C, D);

  free(A);
  free(C);
  free(D);
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