#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -fsyntax-only -fopenmp -verify %s

// RUN: %clang_cc1 -fsyntax-only -fopenmp-simd -verify %s

// expected-error@+1 {{unexpected OpenMP directive '#pragma omp target teams distribute simd'}}
#pragma omp target teams distribute simd

// expected-error@+1 {{unexpected OpenMP directive '#pragma omp target teams distribute simd'}}
#pragma omp target teams distribute simd foo

void test_no_clause() {
  int i;
#pragma omp target teams distribute simd
dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;

// expected-error@+2 {{statement after '#pragma omp target teams distribute simd' must be a for loop}}
dummyMethod4();
#pragma omp target teams distribute simd
  ++i;
}

void test_branch_protected_scope() {
  int i = 0;
L1:
  ++i;

  int x[24];

#pragma omp target teams distribute simd
			dummyMethod3();
  for (i = 0; i < 16; ++i) {
    if (i == 5)
      goto L1; // expected-error {{use of undeclared label 'L1'}}
    else if (i == 6)
      return; // expected-error {{cannot return from OpenMP region}}
    else if (i == 7)
      goto L2;
    else if (i == 8) {
    L2:
      x[i]++;
    }
  }
			dummyMethod4();

  if (x[0] == 0)
    goto L2; // expected-error {{use of undeclared label 'L2'}}
  else if (x[1] == 1)
    goto L1;
}

void test_invalid_clause() {
  int i;
// expected-warning@+1 {{extra tokens at the end of '#pragma omp target teams distribute simd' are ignored}}
#pragma omp target teams distribute simd foo bar
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
}

void test_non_identifiers() {
  int i, x;

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target teams distribute simd' are ignored}}
#pragma omp target teams distribute simd;
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target teams distribute simd' are ignored}}
#pragma omp target teams distribute simd private(x);
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target teams distribute simd' are ignored}}
#pragma omp target teams distribute simd, private(x);
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
}

extern int foo();

void test_collapse() {
  int i;
// expected-error@+1 {{expected '('}}
#pragma omp target teams distribute simd collapse
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
#pragma omp target teams distribute simd collapse(
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd collapse()
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
#pragma omp target teams distribute simd collapse(,
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{expected expression}}  expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
#pragma omp target teams distribute simd collapse(, )
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-warning@+2 {{extra tokens at the end of '#pragma omp target teams distribute simd' are ignored}}
// expected-error@+1 {{expected '('}}
#pragma omp target teams distribute simd collapse 4)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4,
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4, )
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4 4)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4, , 4)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
#pragma omp target teams distribute simd collapse(4)
			dummyMethod3();
  for (int i1 = 0; i1 < 16; ++i1)
    for (int i2 = 0; i2 < 16; ++i2)
      for (int i3 = 0; i3 < 16; ++i3)
        for (int i4 = 0; i4 < 16; ++i4)
          foo();
			dummyMethod4();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
#pragma omp target teams distribute simd collapse(4, 8)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target teams distribute simd', but found only 1}}
			dummyMethod4();
// expected-error@+1 {{expression is not an integer constant expression}}
#pragma omp target teams distribute simd collapse(2.5)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{expression is not an integer constant expression}}
#pragma omp target teams distribute simd collapse(foo())
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
#pragma omp target teams distribute simd collapse(-5)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
#pragma omp target teams distribute simd collapse(0)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
#pragma omp target teams distribute simd collapse(5 - 5)
			dummyMethod3();
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod4();

// expected-error@+4 {{OpenMP constructs may not be nested inside a simd region}}
#pragma omp target teams distribute simd collapse(2) firstprivate(i)
  for (i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j)
											dummyMethod1();
#pragma omp parallel for reduction(+ : i, j)
      for (int k = 0; k < 16; ++k)
        i += j;
											dummyMethod2();
}

void test_private() {
  int i;
// expected-error@+2 {{expected expression}}
// expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
#pragma omp target teams distribute simd private(
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd private(,
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd private(, )
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd private()
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd private(int)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected variable name}}
#pragma omp target teams distribute simd private(0)
  for (i = 0; i < 16; ++i)
    ;

  int x, y, z;
#pragma omp target teams distribute simd private(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp target teams distribute simd private(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp target teams distribute simd private(x, y, z)
  for (i = 0; i < 16; ++i) {
    x = y * i + z;
  }
}

void test_lastprivate() {
  int i;
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd lastprivate(
  for (i = 0; i < 16; ++i)
    ;

// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd lastprivate(,
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd lastprivate(, )
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd lastprivate()
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd lastprivate(int)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected variable name}}
#pragma omp target teams distribute simd lastprivate(0)
  for (i = 0; i < 16; ++i)
    ;

  int x, y, z;
#pragma omp target teams distribute simd lastprivate(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp target teams distribute simd lastprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp target teams distribute simd lastprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
}

void test_firstprivate() {
  int i;
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd firstprivate(
  for (i = 0; i < 16; ++i)
    ;

// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd firstprivate(,
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 2 {{expected expression}}
#pragma omp target teams distribute simd firstprivate(, )
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd firstprivate()
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected expression}}
#pragma omp target teams distribute simd firstprivate(int)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{expected variable name}}
#pragma omp target teams distribute simd firstprivate(0)
  for (i = 0; i < 16; ++i)
    ;

  int x, y, z;
// expected-error@+1 {{lastprivate variable cannot be firstprivate}} expected-note@+1 {{defined as lastprivate}}
#pragma omp target teams distribute simd lastprivate(x) firstprivate(x)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 2 {{lastprivate variable cannot be firstprivate}} expected-note@+1 2 {{defined as lastprivate}}
#pragma omp target teams distribute simd lastprivate(x, y) firstprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 3 {{lastprivate variable cannot be firstprivate}} expected-note@+1 3 {{defined as lastprivate}}
#pragma omp target teams distribute simd lastprivate(x, y, z) firstprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{the value of 'simdlen' parameter must be less than or equal to the value of the 'safelen' parameter}}
#pragma omp target teams distribute simd simdlen(64) safelen(8)
  for (i = 0; i < 16; ++i)
    ;
}

void test_loop_messages() {
  float a[100], b[100], c[100];
// expected-error@+2 {{variable must be of integer or pointer type}}
#pragma omp target teams distribute simd
  for (float fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
// expected-error@+2 {{variable must be of integer or pointer type}}
#pragma omp target teams distribute simd
  for (double fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
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