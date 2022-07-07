/**
 * fdtd2d.c: This file was adapted from PolyBench/GPU 1.0 test suite
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
#define PERCENT_DIFF_ERROR_THRESHOLD 10.05

#define GPU_DEVICE 1

/* Problem size */
#ifdef MINI_DATASET
#define tmax 20
#define NX 20
#define NY 20
#endif

#ifdef SMALL_DATASET
#define tmax 40
#define NX 80
#define NY 80
#endif

#ifdef MEDIUM_DATASET
#define tmax 100
#define NX 250
#define NY 250
#endif

#ifdef LARGE_DATASET
#define tmax 500
#define NX 1200
#define NY 1200
#endif

#ifdef EXTRALARGE_DATASET
#define tmax 1000
#define NX 2400
#define NY 2400
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_arrays(DATA_TYPE *restrict _fict_, DATA_TYPE *restrict ex,
                 DATA_TYPE *restrict ey, DATA_TYPE *restrict hz) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < tmax; i++) {
    _fict_[i] = (DATA_TYPE)i;
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NX; i++) {
    for (j = 0; j < NY; j++) {
      ex[i * NY + j] = ((DATA_TYPE)i * (j + 1) + 1) / NX;
      ey[i * NY + j] = ((DATA_TYPE)(i - 1) * (j + 2) + 2) / NX;
      hz[i * NY + j] = ((DATA_TYPE)(i - 9) * (j + 4) + 3) / NX;
    }
  }
			dummyMethod4();
}

void init_array_hz(DATA_TYPE *restrict hz) {
  int i, j;

			dummyMethod3();
  for (i = 0; i < NX; i++) {
    for (j = 0; j < NY; j++) {
      hz[i * NY + j] = ((DATA_TYPE)(i - 9) * (j + 4) + 3) / NX;
    }
  }
			dummyMethod4();
}

void compareResults(DATA_TYPE *hz1, DATA_TYPE *hz2) {
  int i, j, fail;
  fail = 0;

			dummyMethod3();
  for (i = 0; i < NX; i++) {
    for (j = 0; j < NY; j++) {
      if (percentDiff(hz1[i * NY + j], hz2[i * NY + j]) >
          PERCENT_DIFF_ERROR_THRESHOLD) {
        fail++;
      }
    }
  }
			dummyMethod4();

  // Print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f "
         "Percent: %d\n",
         PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

void runFdtd(DATA_TYPE *restrict _fict_, DATA_TYPE *restrict ex,
             DATA_TYPE *restrict ey, DATA_TYPE *restrict hz) {
  int t, i, j;

			dummyMethod3();
  for (t = 0; t < tmax; t++) {
    for (j = 0; j < NY; j++) {
      ey[0 * NY + j] = _fict_[t];
    }

    for (i = 1; i < NX; i++) {
      for (j = 0; j < NY; j++) {
        ey[i * NY + j] =
            ey[i * NY + j] - 0.5 * (hz[i * NY + j] - hz[(i - 1) * NY + j]);
      }
    }

    for (i = 0; i < NX; i++) {
      for (j = 1; j < NY; j++) {
        ex[i * (NY + 1) + j] = ex[i * (NY + 1) + j] -
                               0.5 * (hz[i * NY + j] - hz[i * NY + (j - 1)]);
      }
    }

    for (i = 0; i < NX; i++) {
      for (j = 0; j < NY; j++) {
        hz[i * NY + j] =
            hz[i * NY + j] -
            0.7 * (ex[i * (NY + 1) + (j + 1)] - ex[i * (NY + 1) + j] +
                   ey[(i + 1) * NY + j] - ey[i * NY + j]);
      }
    }
  }
			dummyMethod4();
}

void GPU__runFdtd(DATA_TYPE *restrict _fict_, DATA_TYPE *restrict ex,
                  DATA_TYPE *restrict ey, DATA_TYPE *restrict hz) {
  int t, i, j;

  char RST_AI1 = 0;
  RST_AI1 |= !((_fict_ + 0 > ex + 62750)
  || (ex + 0 > _fict_ + 100));
  RST_AI1 |= !((_fict_ + 0 > ey + 62750)
  || (ey + 0 > _fict_ + 100));
  RST_AI1 |= !((_fict_ + 0 > hz + 62500)
  || (hz + 0 > _fict_ + 100));
  RST_AI1 |= !((ex + 0 > ey + 62750)
  || (ey + 0 > ex + 62750));
  RST_AI1 |= !((ex + 0 > hz + 62500)
  || (hz + 0 > ex + 62750));
  RST_AI1 |= !((ey + 0 > hz + 62500)
  || (hz + 0 > ey + 62750));
  #pragma omp target data map(to: _fict_[0:100]) map(tofrom: ex[0:62750],ey[0:62750],hz[0:62500]) if(!RST_AI1)
  #pragma omp target if(!RST_AI1)
  for (t = 0; t < tmax; t++) {
							dummyMethod1();
#pragma omp parallel for
    for (j = 0; j < NY; j++) {
      ey[0 * NY + j] = _fict_[t];
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for collapse(2)
    for (i = 1; i < NX; i++) {
      for (j = 0; j < NY; j++) {
        ey[i * NY + j] =
            ey[i * NY + j] - 0.5 * (hz[i * NY + j] - hz[(i - 1) * NY + j]);
      }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for collapse(2)
    for (i = 0; i < NX; i++) {
      for (j = 1; j < NY; j++) {
        ex[i * (NY + 1) + j] = ex[i * (NY + 1) + j] -
                               0.5 * (hz[i * NY + j] - hz[i * NY + (j - 1)]);
      }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for collapse(2)
    for (i = 0; i < NX; i++) {
      for (j = 0; j < NY; j++) {
        hz[i * NY + j] =
            hz[i * NY + j] -
            0.7 * (ex[i * (NY + 1) + (j + 1)] - ex[i * (NY + 1) + j] +
                   ey[(i + 1) * NY + j] - ey[i * NY + j]);
      }
    }
							dummyMethod2();
  }
}

int main() {
  double t_start, t_end;

  DATA_TYPE *_fict_;
  DATA_TYPE *ex;
  DATA_TYPE *ey;
  DATA_TYPE *hz;
  DATA_TYPE *hz_outputFromGpu;

  _fict_ = (DATA_TYPE *)malloc(tmax * sizeof(DATA_TYPE));
  ex = (DATA_TYPE *)malloc(NX * (NY + 1) * sizeof(DATA_TYPE));
  ey = (DATA_TYPE *)malloc((NX + 1) * NY * sizeof(DATA_TYPE));
  hz = (DATA_TYPE *)malloc(NX * NY * sizeof(DATA_TYPE));
  hz_outputFromGpu = (DATA_TYPE *)malloc(NX * NY * sizeof(DATA_TYPE));

  fprintf(stdout, "<< 2-D Finite Different Time Domain Kernel >>\n");

  init_arrays(_fict_, ex, ey, hz);
  init_array_hz(hz_outputFromGpu);

  t_start = rtclock();
  GPU__runFdtd(_fict_, ex, ey, hz_outputFromGpu);
  t_end = rtclock();

  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

  t_start = rtclock();
  runFdtd(_fict_, ex, ey, hz);
  t_end = rtclock();

  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  compareResults(hz, hz_outputFromGpu);

  free(_fict_);
  free(ex);
  free(ey);
  free(hz);
  free(hz_outputFromGpu);

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