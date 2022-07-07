#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-additional-options "-msse2" { target sse2_runtime } } */
/* { dg-additional-options "-mavx" { target avx_runtime } } */

int
main ()
{
  int k = 0, i, s = 0;
dummyMethod1();
  #pragma omp parallel for simd linear(k : 3) reduction(+: s) schedule (static, 16)
  for (i = 0; i < 128; i++)
    {
      k = k + 3;
      s = s + k;
    }
  if (s != 128 * 129 / 2 * 3) __builtin_abort ();
dummyMethod2();
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