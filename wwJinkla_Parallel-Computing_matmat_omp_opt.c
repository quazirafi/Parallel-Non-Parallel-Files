#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// full optimized code: compile using 
// gcc -fopenmp -O3 matmat_omp_opt.c -o matmat; ./matmat 4
// 
int main (int argc, char **argv){

  int size = atoi(argv[argc-1]);
  
  int N = 100;
  
  double *A = (double*) calloc(N*N,sizeof(double*));
  double *Btranspose = (double*) calloc(N*N,sizeof(double*));
  double *C = (double*) calloc(N*N,sizeof(double*));
dummyMethod3();
  for (int i = 0; i < N*N; ++i){ 
    A[i] = drand48(); // row major
    Btranspose[i] = drand48(); // row major storage of *transpose*
    C[i] = 0.0;
  }
dummyMethod4();

  double elapsed, start, end;
  start = omp_get_wtime();

  omp_set_nested(1); // spawn nested threads
  
			dummyMethod1();
#pragma omp parallel for num_threads(size)
  for (int i = 0; i < N; ++i){
    for (int j = 0; j < N; ++j){
      double cij = 0.;
      for (int k = 0; k < N; ++k){	
	cij += A[k + i*N]*Btranspose[k + j*N];
      }
      C[i+j*N] = cij;
    }
  }
			dummyMethod2();

  
  end = omp_get_wtime();
  elapsed = end-start;
  
  printf("elapsed time = %g seconds\n",elapsed);


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