/**
 * bicg.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *           Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
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

// Error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.7

/* Problem size. */
#ifdef MINI_DATASET
#define NX 256
#define NY 256
#endif

#ifdef SMALL_DATASET
#define NX 512
#define NY 512
#endif

#ifdef MEDIUM_DATASET
#define NX 1024
#define NY 1024
#endif

#ifdef LARGE_DATASET
#define NX 4096
#define NY 4096
#endif

#ifdef EXTRALARGE_DATASET
#define NX 8192
#define NY 8192
#endif

#define GPU_DEVICE 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *restrict A, DATA_TYPE *restrict p,
                DATA_TYPE *restrict r) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < NX; i++) {
    r[i] = i * M_PI;
    for (j = 0; j < NY; j++) {
      A[i * NY + j] = ((DATA_TYPE)i * j) / NX;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NY; i++) {
    p[i] = i * M_PI;
  }
			dummyMethod4();
}

void compareResults(DATA_TYPE *restrict s, DATA_TYPE *restrict s_outputFromGpu,
                    DATA_TYPE *restrict q,
                    DATA_TYPE *restrict q_outputFromGpu) {
  int i, fail;
  fail = 0;

  // Compare s with s_cuda
			dummyMethod3();
  for (i = 0; i < NX; i++) {
    if (percentDiff(q[i], q_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD) {
      fail++;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NY; i++) {
    if (percentDiff(s[i], s_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD) {
      fail++;
    }
  }
			dummyMethod4();

  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f "
         "Percent: %d\n",
         PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

void bicg_cpu(DATA_TYPE *restrict A, DATA_TYPE *restrict r,
              DATA_TYPE *restrict s, DATA_TYPE *restrict p,
              DATA_TYPE *restrict q) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < NY; i++) {
    s[i] = 0.0;
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NX; i++) {
    q[i] = 0.0;
    for (j = 0; j < NY; j++) {
      s[j] = s[j] + r[i] * A[i * NY + j];
      q[i] = q[i] + A[i * NY + j] * p[j];
    }
  }
			dummyMethod4();
}

void GPU__bicg(DATA_TYPE *restrict A, DATA_TYPE *restrict r,
               DATA_TYPE *restrict s, DATA_TYPE *restrict p,
               DATA_TYPE *restrict q) {
  int i, j;

  char RST_AI1 = 0;
  RST_AI1 |= !((A + 0 > p + 512)
  || (p + 0 > A + 262144));
  RST_AI1 |= !((A + 0 > q + 512)
  || (q + 0 > A + 262144));
  RST_AI1 |= !((A + 0 > r + 512)
  || (r + 0 > A + 262144));
  RST_AI1 |= !((A + 0 > s + 512)
  || (s + 0 > A + 262144));
  RST_AI1 |= !((p + 0 > q + 512)
  || (q + 0 > p + 512));
  RST_AI1 |= !((p + 0 > r + 512)
  || (r + 0 > p + 512));
  RST_AI1 |= !((p + 0 > s + 512)
  || (s + 0 > p + 512));
  RST_AI1 |= !((q + 0 > r + 512)
  || (r + 0 > q + 512));
  RST_AI1 |= !((q + 0 > s + 512)
  || (s + 0 > q + 512));
  RST_AI1 |= !((r + 0 > s + 512)
  || (s + 0 > r + 512));
  #pragma omp target data map(to: A[0:262144],p[0:512],r[0:512]) map(tofrom: q[0:512],s[0:512]) if(!RST_AI1)
  {
  #pragma omp target if(!RST_AI1)
			dummyMethod3();
  for (i = 0; i < NY; i++) {
    s[i] = 0.0;
  }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for collapse(1)
  #pragma omp target if(!RST_AI1)
  for (j = 0; j < NY; j++) {
    for (i = 0; i < NX; i++) {
      s[j] = s[j] + r[i] * A[i * NY + j];
    }
  }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for collapse(1)
  #pragma omp target if(!RST_AI1)
  for (i = 0; i < NX; i++) {
    q[i] = 0.0;
    for (j = 0; j < NY; j++) {
      q[i] = q[i] + A[i * NY + j] * p[j];
    }
  }
			dummyMethod2();
}
}

int main(int argc, char **argv) {
  double t_start, t_end;

  DATA_TYPE *A;
  DATA_TYPE *r;
  DATA_TYPE *s;
  DATA_TYPE *p;
  DATA_TYPE *q;
  DATA_TYPE *s_GPU;
  DATA_TYPE *q_GPU;

  A = (DATA_TYPE *)malloc(NX * NY * sizeof(DATA_TYPE));
  r = (DATA_TYPE *)malloc(NX * sizeof(DATA_TYPE));
  s = (DATA_TYPE *)malloc(NY * sizeof(DATA_TYPE));
  p = (DATA_TYPE *)malloc(NY * sizeof(DATA_TYPE));
  q = (DATA_TYPE *)malloc(NX * sizeof(DATA_TYPE));
  s_GPU = (DATA_TYPE *)malloc(NY * sizeof(DATA_TYPE));
  q_GPU = (DATA_TYPE *)malloc(NX * sizeof(DATA_TYPE));

  fprintf(stdout, "<< BiCG Sub Kernel of BiCGStab Linear Solver >>\n");

  init_array(A, p, r);

  t_start = rtclock();
  GPU__bicg(A, r, s_GPU, p, q_GPU);
  t_end = rtclock();

  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

  t_start = rtclock();
  bicg_cpu(A, r, s, p, q);
  t_end = rtclock();

  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(s, s_GPU, q, q_GPU);

  free(A);
  free(r);
  free(s);
  free(p);
  free(q);
  free(s_GPU);
  free(q_GPU);

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