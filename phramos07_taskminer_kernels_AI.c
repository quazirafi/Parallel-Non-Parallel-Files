#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifndef taskminerutils
#define taskminerutils
static int taskminer_depth_cutoff = 0;
#define DEPTH_CUTOFF omp_get_num_threads()
char cutoff_test = 0;
#endif
/***************************************************************************
 *cr
 *cr            (C) Copyright 2010 The Board of Trustees of the
 *cr                        University of Illinois
 *cr                         All Rights Reserved
 *cr
 ***************************************************************************/

#include "common.h"

void cpu_stencilGPU(float c0, float c1, float *A0, float *Anext, const int nx,
                    const int ny, const int nz) {

  int i, j, k;

#pragma omp target device(1)
#pragma omp target map(to : A0[ : nx *ny *nz]) \
    map(tofrom : Anext[ : nx *ny *nz])
			dummyMethod1();
#pragma omp parallel for
  for (k = 1; k < nz - 1; k++) {
    for (j = 1; j < ny - 1; j++) {
      for (i = 1; i < nx - 1; i++) {
        Anext[Index3D(nx, ny, i, j, k)] = (A0[Index3D(nx, ny, i, j, k + 1)] +
                                           A0[Index3D(nx, ny, i, j, k - 1)] +
                                           A0[Index3D(nx, ny, i, j + 1, k)] +
                                           A0[Index3D(nx, ny, i, j - 1, k)] +
                                           A0[Index3D(nx, ny, i + 1, j, k)] +
                                           A0[Index3D(nx, ny, i - 1, j, k)]) *
                                              c1 -
                                          A0[Index3D(nx, ny, i, j, k)] * c0;
      }
    }
  }
			dummyMethod2();
}

void cpu_stencilCPU(float c0, float c1, float *A0, float *Anext, const int nx,
                    const int ny, const int nz) {

  int i, j, k;
			dummyMethod3();
  for (k = 1; k < nz - 1; k++) {
    for (j = 1; j < ny - 1; j++) {
      for (i = 1; i < nx - 1; i++) {
        Anext[Index3D(nx, ny, i, j, k)] = (A0[Index3D(nx, ny, i, j, k + 1)] +
                                           A0[Index3D(nx, ny, i, j, k - 1)] +
                                           A0[Index3D(nx, ny, i, j + 1, k)] +
                                           A0[Index3D(nx, ny, i, j - 1, k)] +
                                           A0[Index3D(nx, ny, i + 1, j, k)] +
                                           A0[Index3D(nx, ny, i - 1, j, k)]) *
                                              c1 -
                                          A0[Index3D(nx, ny, i, j, k)] * c0;
      }
    }
  }
			dummyMethod4();
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