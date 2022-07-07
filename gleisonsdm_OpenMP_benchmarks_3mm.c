/**
 * 3mm.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../../common/polybenchUtilFuncts.h"

// define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.05

/* Problem size. */
#define NI 512
#define NJ 512
#define NK 512
#define NL 512
#define NM 512

#define GPU_DEVICE 1

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C, DATA_TYPE *D) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NK; j++) {
      A[i * NK + j] = ((DATA_TYPE)i * j) / NI;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NK; i++) {
    for (j = 0; j < NJ; j++) {
      B[i * NJ + j] = ((DATA_TYPE)i * (j + 1)) / NJ;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NJ; i++) {
    for (j = 0; j < NM; j++) {
      C[i * NM + j] = ((DATA_TYPE)i * (j + 3)) / NL;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NM; i++) {
    for (j = 0; j < NL; j++) {
      D[i * NL + j] = ((DATA_TYPE)i * (j + 2)) / NK;
    }
  }
			dummyMethod4();
}

void compareResults(DATA_TYPE *G, DATA_TYPE *G_outputFromGpu) {
  int i, j, fail;
  fail = 0;

			dummyMethod3();
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NL; j++) {
      if (percentDiff(G[i * NL + j], G_outputFromGpu[i * NL + j]) >
          PERCENT_DIFF_ERROR_THRESHOLD) {
        fail++;
      }
    }
  }
			dummyMethod4();

  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f "
         "Percent: %d\n",
         PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

void mm3_cpu(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C, DATA_TYPE *D,
             DATA_TYPE *E, DATA_TYPE *F, DATA_TYPE *G) {
  int i, j, k;

  /* E := A*B */
			dummyMethod3();
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NJ; j++) {
      E[i * NJ + j] = 0;
      for (k = 0; k < NK; ++k) {
        E[i * NJ + j] += A[i * NK + k] * B[k * NJ + j];
      }
    }
  }
			dummyMethod4();

  /* F := C*D */
			dummyMethod3();
  for (i = 0; i < NJ; i++) {
    for (j = 0; j < NL; j++) {
      F[i * NL + j] = 0;
      for (k = 0; k < NM; ++k) {
        F[i * NL + j] += C[i * NM + k] * D[k * NL + j];
      }
    }
  }
			dummyMethod4();

  /* G := E*F */
			dummyMethod3();
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NL; j++) {
      G[i * NL + j] = 0;
      for (k = 0; k < NJ; ++k) {
        G[i * NL + j] += E[i * NJ + k] * F[k * NL + j];
      }
    }
  }
			dummyMethod4();
}

void mm3_OMP(DATA_TYPE *A, DATA_TYPE *B, DATA_TYPE *C, DATA_TYPE *D,
             DATA_TYPE *E, DATA_TYPE *F, DATA_TYPE *G) {
  int i, j, k;

/* E := A*B */
#pragma omp target device(GPU_DEVICE)
#pragma omp target map(to : A[ : NI *NK], B[ : NK *NJ]) map(from : E[ : NI *NJ])
			dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NJ; j++) {
      E[i * NJ + j] = 0;
      for (k = 0; k < NK; ++k) {
        E[i * NJ + j] += A[i * NK + k] * B[k * NJ + j];
      }
    }
  }
			dummyMethod2();

/* F := C*D */
#pragma omp target map(to : C[ : NJ *NM], D[ : NM *NL]) map(from : F[ : NJ *NL])
			dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < NJ; i++) {
    for (j = 0; j < NL; j++) {
      F[i * NL + j] = 0;
      for (k = 0; k < NM; ++k) {
        F[i * NL + j] += C[i * NM + k] * D[k * NL + j];
      }
    }
  }
			dummyMethod2();

/* G := E*F */
#pragma omp target map(to : E[ : NI *NJ], F[ : NJ *NL]) map(from : G[ : NI *NL])
			dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < NI; i++) {
    for (j = 0; j < NL; j++) {
      G[i * NL + j] = 0;
      for (k = 0; k < NJ; ++k) {
        G[i * NL + j] += E[i * NJ + k] * F[k * NL + j];
      }
    }
  }
			dummyMethod2();
}

int main(int argc, char **argv) {
  double t_start, t_end;

  DATA_TYPE *A;
  DATA_TYPE *B;
  DATA_TYPE *C;
  DATA_TYPE *D;
  DATA_TYPE *E;
  DATA_TYPE *F;
  DATA_TYPE *G;
  DATA_TYPE *G_outputFromGpu;

  A = (DATA_TYPE *)malloc(NI * NK * sizeof(DATA_TYPE));
  B = (DATA_TYPE *)malloc(NK * NJ * sizeof(DATA_TYPE));
  C = (DATA_TYPE *)malloc(NJ * NM * sizeof(DATA_TYPE));
  D = (DATA_TYPE *)malloc(NM * NL * sizeof(DATA_TYPE));
  E = (DATA_TYPE *)malloc(NI * NJ * sizeof(DATA_TYPE));
  F = (DATA_TYPE *)malloc(NJ * NL * sizeof(DATA_TYPE));
  G = (DATA_TYPE *)malloc(NI * NL * sizeof(DATA_TYPE));
  G_outputFromGpu = (DATA_TYPE *)malloc(NI * NL * sizeof(DATA_TYPE));

  fprintf(
      stdout,
      "<< Linear Algebra: 3 Matrix Multiplications (E=A.B; F=C.D; G=E.F) >>\n");

  init_array(A, B, C, D);

  t_start = rtclock();
  mm3_OMP(A, B, C, D, E, F, G_outputFromGpu);
  t_end = rtclock();

  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

  t_start = rtclock();
  mm3_cpu(A, B, C, D, E, F, G);
  t_end = rtclock();

  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(G, G_outputFromGpu);

  free(A);
  free(B);
  free(C);
  free(D);
  free(E);
  free(F);
  free(G);
  free(G_outputFromGpu);

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