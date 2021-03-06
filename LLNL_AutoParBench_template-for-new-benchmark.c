/**
 * template.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 * License: /LICENSE.OSU.txt
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Include polybench common header. */
#include "../polybench/polybench.h"

/* Include benchmark-specific header. */
/* Default data type is double, default size is N=1024. */
#include "template-for-new-benchmark.h"


/* Array initialization. */
static
void init_array(int n, DATA_TYPE POLYBENCH_2D(C,N,N,n,n))
{
  int i, j;

dummyMethod1();
  #pragma omp parallel for firstprivate(j ,C ,i ) 
  for (i = 0; i < n; i++)
    #pragma omp parallel for firstprivate(j ,C ,i ) 
    for (j = 0; j < n; j++)
      C[i][j] = 42;
}
dummyMethod2();


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n, DATA_TYPE POLYBENCH_2D(C,N,N,n,n))
{
  int i, j;

			dummyMethod3();
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
	fprintf (stderr, DATA_PRINTF_MODIFIER, C[i][j]);
	if (i % 20 == 0) fprintf (stderr, "\n");
    }
			dummyMethod4();
  fprintf (stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_template(int n, DATA_TYPE POLYBENCH_2D(C,N,N,n,n))
{
  int i, j;

			dummyMethod1();
  #pragma omp parallel for firstprivate(j ,C ,i ) 
  for (i = 0; i < _PB_N; i++)
			dummyMethod2();
    #pragma omp parallel for firstprivate(j ,C ,i ) 
    for (j = 0; j < _PB_N; j++)
      C[i][j] += 42;

}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);

  /* Initialize array(s). */
  init_array (n, POLYBENCH_ARRAY(C));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_template (n, POLYBENCH_ARRAY(C));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n,  POLYBENCH_ARRAY(C)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(C);

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