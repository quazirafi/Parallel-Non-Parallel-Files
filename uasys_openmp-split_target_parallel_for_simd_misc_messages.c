#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -fsyntax-only -fopenmp -verify %s

// expected-error@+1 {{unexpected OpenMP directive '#pragma omp target parallel for simd'}}
dummyMethod1();
#pragma omp target parallel for simd

// expected-error@+1 {{unexpected OpenMP directive '#pragma omp target parallel for simd'}}
dummyMethod1();
#pragma omp target parallel for simd foo

void test_no_clause() {
  int i;
dummyMethod1();
#pragma omp target parallel for simd
  for (i = 0; i < 16; ++i)
    ;

dummyMethod2();
dummyMethod2();
// expected-error@+2 {{statement after '#pragma omp target parallel for simd' must be a for loop}}
dummyMethod2();
dummyMethod1();
#pragma omp target parallel for simd
  ++i;
}

void test_branch_protected_scope() {
  int i = 0;
L1:
  ++i;

  int x[24];

			dummyMethod1();
#pragma omp target parallel for simd
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
			dummyMethod2();
  }
dummyMethod2();

  if (x[0] == 0)
    goto L2; // expected-error {{use of undeclared label 'L2'}}
  else if (x[1] == 1)
    goto L1;
}

void test_invalid_clause() {
  int i;
// expected-warning@+1 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
			dummyMethod1();
#pragma omp target parallel for simd foo bar
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
}

void test_non_identifiers() {
  int i, x;

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
			dummyMethod1();
#pragma omp target parallel for simd;
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
			dummyMethod1();
#pragma omp target parallel for simd private(x);
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

// expected-warning@+1 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
			dummyMethod1();
#pragma omp target parallel for simd, private(x);
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
}

extern int foo();

void test_collapse() {
  int i;
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd collapse
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd collapse()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}  expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-warning@+2 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd collapse 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4,
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4, )
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4)
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4 4)
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4, , 4)
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd collapse(4)
  for (int i1 = 0; i1 < 16; ++i1)
    for (int i2 = 0; i2 < 16; ++i2)
      for (int i3 = 0; i3 < 16; ++i3)
        for (int i4 = 0; i4 < 16; ++i4)
          foo();
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}} expected-note@+1 {{as specified in 'collapse' clause}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(4, 8)
  for (i = 0; i < 16; ++i)
    ; // expected-error {{expected 4 for loops after '#pragma omp target parallel for simd', but found only 1}}
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(2.5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(foo())
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(-5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'collapse' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-note@+1 {{defined as firstprivate}}
			dummyMethod1();
#pragma omp target parallel for simd collapse(2) firstprivate(i)
  for (i = 0; i < 16; ++i)
// expected-note@+1 {{variable with automatic storage duration is predetermined as private; perhaps you forget to enclose 'omp for' directive into a parallel or another task region?}}
    for (int j = 0; j < 16; ++j)
// expected-error@+2 2 {{reduction variable must be shared}}
// expected-error@+1 {{OpenMP constructs may not be nested inside a simd region}}
			dummyMethod2();
#pragma omp for reduction(+ : i, j)
      for (int k = 0; k < 16; ++k)
        i += j;
}

void test_private() {
  int i;
// expected-error@+2 {{expected expression}}
// expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd private(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd private(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd private(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd private()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd private(int)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected variable name}}
			dummyMethod1();
#pragma omp target parallel for simd private(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

  int x, y, z;
			dummyMethod1();
#pragma omp target parallel for simd private(x)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd private(x, y)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd private(x, y, z)
  for (i = 0; i < 16; ++i) {
    x = y * i + z;
  }
			dummyMethod2();
}

void test_lastprivate() {
  int i;
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(int)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected variable name}}
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

  int x, y, z;
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
}

void test_firstprivate() {
  int i;
// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

// expected-error@+2 {{expected ')'}} expected-note@+2 {{to match this '('}}
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 2 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate(int)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected variable name}}
			dummyMethod1();
#pragma omp target parallel for simd firstprivate(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();

  int x, y, z;
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x) firstprivate(x)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x, y) firstprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd lastprivate(x, y, z) firstprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
}

void test_loop_messages() {
  float a[100], b[100], c[100];
// expected-error@+2 {{variable must be of integer or pointer type}}
			dummyMethod1();
#pragma omp target parallel for simd
  for (float fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
			dummyMethod2();
// expected-error@+2 {{variable must be of integer or pointer type}}
			dummyMethod1();
#pragma omp target parallel for simd
  for (double fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
			dummyMethod2();
}

void test_safelen() {
  int i;
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd safelen()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}  expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-warning@+2 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd safelen(4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4, , 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd safelen(4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(4, 8)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(2.5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(foo())
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'safelen' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(-5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'safelen' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'safelen' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd safelen(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
}

void test_simdlen() {
  int i;
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen()
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}} expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expected expression}}  expected-error@+1 {{expected ')'}} expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-warning@+2 {{extra tokens at the end of '#pragma omp target parallel for simd' are ignored}}
// expected-error@+1 {{expected '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4,
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4, )
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4, , 4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+2 {{expected ')'}}
// expected-note@+1 {{to match this '('}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(4, 8)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(2.5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{expression is not an integer constant expression}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(foo())
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'simdlen' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(-5)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'simdlen' clause must be a strictly positive integer value}}
			dummyMethod1();
#pragma omp target parallel for simd simdlen(0)
  for (i = 0; i < 16; ++i)
    ;
			dummyMethod2();
// expected-error@+1 {{argument to 'simdlen' clause must be a strictly positive integer value}}
#pragma omp target parallel for simd simdlen(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
}

void test_safelen_simdlen() {
  int i;
// expected-error@+1 {{the value of 'simdlen' parameter must be less than or equal to the value of the 'safelen' parameter}}
#pragma omp target parallel for simd simdlen(6) safelen(5)
  for (i = 0; i < 16; ++i)
    ;
// expected-error@+1 {{the value of 'simdlen' parameter must be less than or equal to the value of the 'safelen' parameter}}
#pragma omp target parallel for simd safelen(5) simdlen(6)
  for (i = 0; i < 16; ++i)
    ;
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