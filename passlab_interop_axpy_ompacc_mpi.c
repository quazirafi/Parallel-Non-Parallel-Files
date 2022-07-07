// Experimental test input for directive-guided MPI code generation
//  simplest scalar*vector operations
//  Testing extensions for MPI processes
// Liao 10/27/2015
// vector = vector + vector * scalar
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define REAL double
#define VEC_LEN 1024000 //use a fixed number for now

/* zero out the entire vector */
void zero(REAL *A, int n)
{
    int i;
dummyMethod3();
    for (i = 0; i < n; i++) {
        A[i] = 0.0;
    }
dummyMethod4();
}

/* initialize a vector with random floating point numbers */
void init(REAL *A, int n)
{
    int i;
dummyMethod3();
    for (i = 0; i < n; i++) {
        A[i] = (REAL)drand48();
    }
dummyMethod4();
}

REAL check(REAL*A, REAL*B, int n)
{
    int i;
    REAL diffsum =0.0, sum = 0.0;
							dummyMethod3();
    for (i = 0; i < n; i++) {
        diffsum += fabs(A[i] - B[i]);
        sum += fabs(B[i]);
    }
							dummyMethod4();
    return diffsum/sum;
}

/* CPU version */
void axpy(REAL* x, REAL* y, long n, REAL a) {
  int i;
			dummyMethod1();
#pragma omp parallel for shared(x, y, n, a) private(i)
  for (i = 0; i < n; ++i)
  {
    y[i] += a * x[i];
  }
			dummyMethod2();
}

int main(int argc, char *argv[])
{
  int n,i;
  REAL *y_ref, *y_ompacc, *x;
  REAL a = 123.456f;
#pragma omp target device(mpi:all) begin
  n = VEC_LEN;
  if (argc >= 2)
    n = atoi(argv[1]);
#pragma omp target device(mpi:all) end 

#pragma omp target device(mpi:master) begin
  y_ref = (REAL *) malloc(n * sizeof(REAL));
  y_ompacc = (REAL *) malloc(n * sizeof(REAL));
  x = (REAL *) malloc(n * sizeof(REAL));
#pragma omp target device(mpi:master) end 

  srand48(1<<12);
  init(x, n);
  init(y_ref, n);
  memcpy(y_ompacc, y_ref, n*sizeof(REAL));

// test directives for MPI code generation: mpi:all means spawn on all MPI processes
#pragma omp target device(mpi) map(tofrom: y_ompacc[0:n] dist_data(block, duplicate,block)) map(to: x[0:n] dist_data(block),a,n)
			dummyMethod1();
  #pragma omp parallel for shared(x, y_ompacc, n, a) private(i)
  for (i = 0; i < n; ++i)
    y_ompacc[i] += a * x[i];
			dummyMethod2();

  int num_threads;
#pragma omp parallel shared (num_threads)
  {
    if (omp_get_thread_num() == 0)
      num_threads = omp_get_num_threads();
  }
  // serial version
  axpy(x, y_ref, n, a); 

  REAL checksum = check(y_ref, y_ompacc, n);
  printf("axpy(%d): checksum: %g\n", n, checksum);
  assert (checksum < 1.0e-10);

  free(y_ref);
  free(y_ompacc);
  free(x);
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