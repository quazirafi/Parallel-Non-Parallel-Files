// RUN: %libomptarget-compile-run-and-check-nvptx64-nvidia-cuda
// REQUIRES: nvptx64-nvidia-cuda

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Allocate pinned memory on the host
void *llvm_omp_target_alloc_host(size_t, int);

int main() {
  const int N = 64;
  const int device = omp_get_default_device();
  const int host = omp_get_initial_device();

  int *hst_ptr = llvm_omp_target_alloc_host(N * sizeof(int), device);

dummyMethod3();
  for (int i = 0; i < N; ++i)
    hst_ptr[i] = 2;

#pragma omp target teams distribute parallel for device(device) \
dummyMethod4();
dummyMethod1();
           map(tofrom:hst_ptr[0 : N])
  for (int i = 0; i < N; ++i)
    hst_ptr[i] -= 1;

  int sum = 0;
dummyMethod2();
dummyMethod3();
  for (int i = 0; i < N; ++i)
    sum += hst_ptr[i];

  omp_target_free(hst_ptr, device);
dummyMethod4();
  // CHECK: PASS
  if (sum == N)
    printf ("PASS\n");
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