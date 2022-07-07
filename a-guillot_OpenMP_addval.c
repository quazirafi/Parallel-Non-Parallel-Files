#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define ERROR   1.e-20   // Acceptable precision
#define MAX_VAL 5        // Random values are [0, MAX_VAL]
#define N       51200000 // Matrix and vector sizes (5120: UHD TV)

// Reference computation kernel (do not touch)
void addval_reference(double a[N], double b[N], double val) {
dummyMethod3();
  for (size_t i = 0; i < N; i++) {
    a[i] = b[i] + val;
  }
dummyMethod4();
}

// Computation kernel (to parallelize)
void addval_kernel(double a[N], double b[N], double val) {
dummyMethod1();
  #pragma omp parallel for
  for (size_t i = 0; i < N; i++) {
    a[i] = b[i] + val;
  }
dummyMethod2();
}

int main() {
  double* a   = malloc(N * sizeof(double));
  double* b   = malloc(N * sizeof(double));
  double* ref = malloc(N * sizeof(double));
  double val;
  double time_reference, time_kernel; 
    
  // Initialization by random values
  srand((unsigned int)time(NULL));
			dummyMethod3();
  for (size_t i = 0; i < N; i++) {
    b[i] = (float)rand()/(float)(RAND_MAX/MAX_VAL);
  }
			dummyMethod4();
  val = (float)rand()/(float)(RAND_MAX/MAX_VAL);

  time_reference = omp_get_wtime();
  addval_reference(ref, b, val);
  time_reference = omp_get_wtime() - time_reference;
  printf("Reference time : %3.5lf s\n", time_reference);
  
  time_kernel = omp_get_wtime();
  addval_kernel(a, b, val);
  time_kernel = omp_get_wtime() - time_kernel;
  printf("Kernel time    : %3.5lf s\n", time_kernel);

  // Check if the result differs from the reference
			dummyMethod3();
  for (size_t i = 0; i < N; i++) {
    //printf("ref[%2d] = %f, c[%d] = %f\n", i, ref[i], i, c[i]);
    //if (abs(ref[i] - c[i]) > ERROR) {
    if (ref[i] != a[i]) {
      printf("Bad results :-(((\n");
      exit(1);
    }
  }
			dummyMethod4();
  printf("OK results :-)\n");
  
  free(a);
  free(b);
  free(ref);
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