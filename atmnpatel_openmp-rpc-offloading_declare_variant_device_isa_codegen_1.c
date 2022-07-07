#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -verify -fopenmp -x c -triple %itanium_abi_triple -emit-llvm %s -o - -fopenmp-version=45 | FileCheck %s --check-prefix=GENERIC
// RUN: %clang_cc1 -fopenmp -x c++ -std=c++11 -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -emit-pch -o %t -fopenmp-version=45 %s
// RUN: %clang_cc1 -fopenmp -x c++ -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -std=c++11 -include-pch %t -verify %s -emit-llvm -o - -fopenmp-version=45 | FileCheck %s --check-prefix=GENERIC

// RUN: %clang_cc1 -target-feature +avx512f -verify -fopenmp -x c -triple %itanium_abi_triple -emit-llvm %s -o - -fopenmp-version=45 | FileCheck %s --check-prefix=WITHFEATURE
// RUN: %clang_cc1 -target-feature +avx512f -fopenmp -x c++ -std=c++11 -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -emit-pch -o %t -fopenmp-version=45 %s
// RUN: %clang_cc1 -target-feature +avx512f -fopenmp -x c++ -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -std=c++11 -include-pch %t -verify %s -emit-llvm -o - -fopenmp-version=45 | FileCheck %s --check-prefix=WITHFEATURE

// RUN: %clang_cc1 -verify -fopenmp -x c -triple %itanium_abi_triple -emit-llvm %s -o - | FileCheck %s --check-prefix=GENERIC
// RUN: %clang_cc1 -fopenmp -x c++ -std=c++11 -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -emit-pch -o %t %s
// RUN: %clang_cc1 -fopenmp -x c++ -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -std=c++11 -include-pch %t -verify %s -emit-llvm -o - | FileCheck %s --check-prefix=GENERIC

// RUN: %clang_cc1 -target-feature +avx512f -verify -fopenmp -x c -triple %itanium_abi_triple -emit-llvm %s -o - | FileCheck %s --check-prefix=WITHFEATURE
// RUN: %clang_cc1 -target-feature +avx512f -fopenmp -x c++ -std=c++11 -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -emit-pch -o %t %s
// RUN: %clang_cc1 -target-feature +avx512f -fopenmp -x c++ -triple %itanium_abi_triple -fexceptions -fcxx-exceptions -std=c++11 -include-pch %t -verify %s -emit-llvm -o - | FileCheck %s --check-prefix=WITHFEATURE

// expected-no-diagnostics

// Test taken from PR46338 (by linna su)

#ifndef HEADER
#define HEADER

void base_saxpy(int, float, float *, float *);
void avx512_saxpy(int, float, float *, float *);

#pragma omp declare variant(avx512_saxpy) \
    match(device = {isa(avx512f)})
void base_saxpy(int n, float s, float *x, float *y) {
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < n; i++)
    y[i] = s * x[i] + y[i];
}
dummyMethod2();

void avx512_saxpy(int n, float s, float *x, float *y) {
			dummyMethod1();
#pragma omp parallel for simd simdlen(16) aligned(x, y : 64)
  for (int i = 0; i < n; i++)
    y[i] = s * x[i] + y[i];
			dummyMethod2();
}

void caller(int n, float s, float *x, float *y) {
  // GENERIC:     define {{.*}}void @{{.*}}caller
  // GENERIC:      call void @{{.*}}base_saxpy
  // WITHFEATURE: define {{.*}}void @{{.*}}caller
  // WITHFEATURE:  call void @{{.*}}avx512_saxpy
  base_saxpy(n, s, x, y);
}

  // GENERIC:     define {{.*}}void @{{.*}}variant_caller
  // GENERIC:      call void @{{.*}}avx512_saxpy
  // WITHFEATURE: define {{.*}}void @{{.*}}variant_caller
  // WITHFEATURE:  call void @{{.*}}avx512_saxpy

#endif
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