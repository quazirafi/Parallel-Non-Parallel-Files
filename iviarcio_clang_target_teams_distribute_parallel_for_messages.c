#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -triple x86_64-apple-macos10.7.0 -verify -fopenmp -ferror-limit 100 -o - %s

void foo() {}

int main(int argc, char **argv) {
L1:
  foo();
dummyMethod1();
#pragma omp target teams distribute parallel for
  for (int i = 0; i < 10; ++i) {
    foo();
    goto L1; // expected-error {{use of undeclared label 'L1'}}
  }
dummyMethod2();
  goto L2; // expected-error {{use of undeclared label 'L2'}}
dummyMethod1();
#pragma omp target teams distribute parallel for
  for (int i = 0; i < 10; ++i) {
  L2:
dummyMethod2();
    foo();
  }

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