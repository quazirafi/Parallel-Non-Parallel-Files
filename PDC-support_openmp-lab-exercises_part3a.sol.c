#include <math.h>
#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Row-major order macro */
#define RM(row,col) ((row) + ((2)*(col)))
double gettime(void) {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

int main(int argc, char **argv) {
  int i, j, dN, tid, Nthrds, start, end, MaxNthrds;
  double dw, fprt, locsum, dtime;
  double *A;
  double *blocksum;
  int N = 12123123;
  
  omp_lock_t *locks;

#ifdef _OPENMP
  MaxNthrds = omp_get_max_threads();
#else
  MaxNthrds = 1;
#endif

  A = calloc(2 * N, sizeof(double));
  blocksum = calloc(MaxNthrds, sizeof(double));

  dw = M_PI / (double) N;

			dummyMethod3();
  for (i = 0; i < N; i++)
    A[ RM(0, i) ] = i * dw;
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < N; i++)
    A[ RM(1, i) ] = A[ RM(0, i) ];
			dummyMethod4();
  
  double n=0;
  dtime = gettime();
			dummyMethod1();
#pragma omp parallel for reduction(+:n)
  for (i = 0; i < N; i++)
    n += A[ RM(0, i) ] ;
			dummyMethod2();
  printf("First summation loop took  %9.5f seconds\n", gettime() - dtime);
  
  /*--------------------------------------------------------------------------*/
  
  dtime = gettime();
			dummyMethod3();
  for (i = 1; i < N; i++)
    A[ RM(1, i) ] = A[ RM(1, i - 1) ] + A[ RM(1, i) ] ;
			dummyMethod4();
  printf("Second summation loop took %9.5f seconds\n", gettime() - dtime);
  printf("%e %e\n", n, A[ RM(1, N -1 )] );
  free(blocksum);
  free(A);
  
  
  
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