#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-additional-options "-msse2" { target sse2_runtime } } */
/* { dg-additional-options "-mavx" { target avx_runtime } } */

static inline void
foo (int *b, int *i, int *j, int x)
{
  *b = *b + x + (*i - *i) + (*j - *j);
}

int
main ()
{
  int i, j, b, c = 0;
  i = 4; j = 4; b = 7;
  #pragma omp simd linear(b:2) reduction(+:c)
dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      c = c + (b != 7 + 2 * i);
      foo (&b, &i, &j, 2);
    }
  if (c || i != 64 || b != 7 + 64 * 2)
dummyMethod4();
    __builtin_abort ();
  i = 4; j = 4; b = 7;
  #pragma omp simd linear(b:3) reduction(+:c)
dummyMethod3();
  for (i = 0; i < 64; i += 4)
    {
      c = c + (b != 7 + i / 4 * 3);
      foo (&b, &i, &j, 3);
    }
  if (c || i != 64 || b != 7 + 16 * 3)
dummyMethod4();
    __builtin_abort ();
  i = 4; j = 4; b = 7;
  #pragma omp simd linear(i) linear(b:2) reduction(+:c)
			dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      c = c + (b != 7 + 2 * i);
      foo (&b, &i, &j, 2);
    }
			dummyMethod4();
  if (c || i != 64 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
  #pragma omp simd linear(i:4) linear(b:3) reduction(+:c)
			dummyMethod3();
  for (i = 0; i < 64; i += 4)
    {
      c = c + (b != 7 + i / 4 * 3);
      foo (&b, &i, &j, 3);
    }
			dummyMethod4();
  if (c || i != 64 || b != 7 + 16 * 3)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
  #pragma omp simd collapse (2) linear(b:2) reduction(+:c)
			dummyMethod3();
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	c = c + (b != 7 + 2 * j + 2 * 8 * i);
	foo (&b, &i, &j, 2);
      }
			dummyMethod4();
  if (c || i != 8 || j != 8 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
  #pragma omp simd collapse (2) lastprivate (i, j) linear(b:2) reduction(+:c)
			dummyMethod3();
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	c = c + (b != 7 + 2 * j + 2 * 8 * i);
	foo (&b, &i, &j, 2);
      }
			dummyMethod4();
  if (c || i != 8 || j != 8 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd schedule (static, 4) linear(b:2) reduction(+:c)
  for (i = 0; i < 64; i++)
    {
      c = c + (b != 7 + 2 * i);
      foo (&b, &i, &j, 2);
    }
			dummyMethod2();
  if (c || i != 64 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd schedule (static, 4) linear(b:3) reduction(+:c)
  for (i = 0; i < 64; i += 4)
    {
      c = c + (b != 7 + i / 4 * 3);
      foo (&b, &i, &j, 3);
    }
			dummyMethod2();
  if (c || i != 64 || b != 7 + 16 * 3)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd schedule (static, 4) linear(i) linear(b:2) reduction(+:c)
  for (i = 0; i < 64; i++)
    {
      c = c + (b != 7 + 2 * i);
      foo (&b, &i, &j, 2);
    }
			dummyMethod2();
  if (c || i != 64 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd schedule (static, 4) linear(i:4) linear(b:3) reduction(+:c)
  for (i = 0; i < 64; i += 4)
    {
      c = c + (b != 7 + i / 4 * 3);
      foo (&b, &i, &j, 3);
    }
			dummyMethod2();
  if (c || i != 64 || b != 7 + 16 * 3)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd lastprivate (i, j) collapse (2) schedule (static, 4) linear(b:2) reduction(+:c)
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	c = c + (b != 7 + 2 * j + 2 * 8 * i);
	foo (&b, &i, &j, 2);
      }
			dummyMethod2();
  if (c || i != 8 || j != 8 || b != 7 + 64 * 2)
    __builtin_abort ();
  i = 4; j = 4; b = 7;
			dummyMethod1();
  #pragma omp parallel for simd collapse (2) schedule (static, 4) linear(b:2) reduction(+:c)
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	c = c + (b != 7 + 2 * j + 2 * 8 * i);
	foo (&b, &i, &j, 2);
      }
			dummyMethod2();
  if (c || i != 8 || j != 8 || b != 7 + 64 * 2)
    __builtin_abort ();
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