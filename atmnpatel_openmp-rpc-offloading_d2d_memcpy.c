// RUN: %libomptarget-compile-aarch64-unknown-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-aarch64-unknown-linux-gnu | %fcheck-aarch64-unknown-linux-gnu
// RUN: %libomptarget-compile-powerpc64-ibm-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-powerpc64-ibm-linux-gnu | %fcheck-powerpc64-ibm-linux-gnu
// RUN: %libomptarget-compile-powerpc64le-ibm-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-powerpc64le-ibm-linux-gnu | %fcheck-powerpc64le-ibm-linux-gnu
// RUN: %libomptarget-compile-x86_64-pc-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-x86_64-pc-linux-gnu | %fcheck-x86_64-pc-linux-gnu -allow-empty
// RUN: %libomptarget-compile-nvptx64-nvidia-cuda && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-nvptx64-nvidia-cuda | %fcheck-nvptx64-nvidia-cuda -allow-empty

#include <assert.h>
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int magic_num = 7;

int main(int argc, char *argv[]) {
  const int N = 128;
  const int num_devices = omp_get_num_devices();

  // No target device, just return
  if (num_devices == 0) {
    printf("PASS\n");
    return 0;
  }

  const int src_device = 0;
  int dst_device = num_devices - 1;

  int length = N * sizeof(int);
  int *src_ptr = omp_target_alloc(length, src_device);
  int *dst_ptr = omp_target_alloc(length, dst_device);

  assert(src_ptr && "src_ptr is NULL");
  assert(dst_ptr && "dst_ptr is NULL");

			dummyMethod1();
#pragma omp target teams distribute parallel for device(src_device) \
                   is_device_ptr(src_ptr)
  for (int i = 0; i < N; ++i) {
    src_ptr[i] = magic_num;
  }
			dummyMethod2();

  int rc =
      omp_target_memcpy(dst_ptr, src_ptr, length, 0, 0, dst_device, src_device);

  assert(rc == 0 && "error in omp_target_memcpy");

  int *buffer = malloc(length);

  assert(buffer && "failed to allocate host buffer");

			dummyMethod1();
#pragma omp target teams distribute parallel for device(dst_device) \
                   map(from: buffer[0:N]) is_device_ptr(dst_ptr)
  for (int i = 0; i < N; ++i) {
    buffer[i] = dst_ptr[i] + magic_num;
  }
			dummyMethod2();

			dummyMethod3();
  for (int i = 0; i < N; ++i)
    assert(buffer[i] == 2 * magic_num);
			dummyMethod4();

  printf("PASS\n");

  // Free host and device memory
  free(buffer);
  omp_target_free(src_ptr, src_device);
  omp_target_free(dst_ptr, dst_device);

  return 0;
}

// CHECK: PASS
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