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
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SMALL_FLOAT_VAL 0.00000001f

double rtclock() {
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday(&Tp, &Tzp);
  if (stat != 0)
    printf("Error return from gettimeofday: %d", stat);
  return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

float absVal(float a) {
  if (a < 0) {
    return (a * -1);
  } else {
    return a;
  }
}

float percentDiff(double val1, double val2) {
  double val3 = (val1 >= val2) ? (val1 - val2) : (val2 - val1);
  if (val3 < 0.5) {
    return 0.0f;
  }

  else {
    return 100.0f *
           (absVal(absVal(val1 - val2) / absVal(val1 + SMALL_FLOAT_VAL)));
  }
}

// define the error threshold for the results "not matching"
#define ERROR_THRESHOLD 0.05
#define GPU_DEVICE 1

/* Problem size */
#ifdef MINI_DATASET
#define N 30
#define M 30
#endif

#ifdef SMALL_DATASET
#define N 80
#define M 80
#endif

#ifdef MEDIUM_DATASET
#define N 240
#define M 240
#endif

#ifdef LARGE_DATASET
#define N 1200
#define M 1200
#endif

#ifdef EXTRALARGE_DATASET
#define N 2400
#define M 2400
#endif

/* Declared constant values for alpha and beta */
/* (same as values in PolyBench 2.0) */
#define alpha 12435
#define beta 4546

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE *restrict A, DATA_TYPE *restrict C,
                 DATA_TYPE *restrict D) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      A[i * M + j] = ((DATA_TYPE)i * j) / N;
    }
    for (j = 0; j < M; j++) {
      C[i * M + j] = ((DATA_TYPE)i * j + 2) / N;
      D[i * M + j] = ((DATA_TYPE)i * j + 2) / N;
    }
  }
			dummyMethod4();
}

void compareResults(DATA_TYPE *restrict C, DATA_TYPE *restrict D) {
  int i, j, fail;
  fail = 0;

  // Compare C with D
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      if (percentDiff(C[i * M + j], D[i * M + j]) > ERROR_THRESHOLD) {
        fail++;
      }
    }
  }
			dummyMethod4();

  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f "
         "Percent: %d\n",
         ERROR_THRESHOLD, fail);
}

void syrk(DATA_TYPE *restrict A, DATA_TYPE *restrict C) {
  int i, j, k;

			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      C[i * M + j] *= beta;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      for (k = 0; k < M; k++) {
        C[i * N + j] += alpha * A[i * M + k] * A[j * M + k];
      }
    }
  }
			dummyMethod4();
}

void GPU__syrk(DATA_TYPE *restrict A, DATA_TYPE *restrict D) {
  int i, j;
  double t_start, t_end;

  t_start = rtclock();

			dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      D[i * M + j] *= beta;
    }
  }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for collapse(2)
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      int k;
      for (k = 0; k < M; k++) {
        D[i * M + j] += alpha * A[i * M + k] * A[j * M + k];
      }
    }
  }
			dummyMethod2();

  t_end = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);
}

int main() {
  double t_start, t_end;

  DATA_TYPE *A;
  DATA_TYPE *C;
  DATA_TYPE *D;

  A = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
  C = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));
  D = (DATA_TYPE *)malloc(N * M * sizeof(DATA_TYPE));

  fprintf(stdout, "<< Symmetric rank-k operations >>\n");

  init_arrays(A, C, D);
  GPU__syrk(A, D);

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