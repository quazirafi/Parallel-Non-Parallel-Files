// RUN: %libomptarget-compile-aarch64-unknown-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-aarch64-unknown-linux-gnu | %fcheck-aarch64-unknown-linux-gnu
// RUN: %libomptarget-compile-powerpc64-ibm-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-powerpc64-ibm-linux-gnu | %fcheck-powerpc64-ibm-linux-gnu
// RUN: %libomptarget-compile-powerpc64le-ibm-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-powerpc64le-ibm-linux-gnu | %fcheck-powerpc64le-ibm-linux-gnu
// RUN: %libomptarget-compile-x86_64-pc-linux-gnu && env OMP_MAX_ACTIVE_LEVELS=2 %libomptarget-run-x86_64-pc-linux-gnu | %fcheck-x86_64-pc-linux-gnu -allow-empty
#include <assert.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
  const int num_threads = 64, N = 128;
  int array[num_threads] = {0};

dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < num_threads; ++i) {
    int tmp[N];

    for (int j = 0; j < N; ++j) {
      tmp[j] = i;
    }

#pragma omp target teams distribute parallel for map(tofrom : tmp)
dummyMethod2();
    for (int j = 0; j < N; ++j) {
      tmp[j] += j;
    }

    for (int j = 0; j < N; ++j) {
      array[i] += tmp[j];
    }
  }

  // Verify
			dummyMethod3();
  for (int i = 0; i < num_threads; ++i) {
    const int ref = (0 + N - 1) * N / 2 + i * N;
    assert(array[i] == ref);
  }
			dummyMethod4();

  printf("PASS\n");

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