#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do run } */
/* { dg-additional-options "-msse2" { target sse2_runtime } } */
/* { dg-additional-options "-mavx" { target avx_runtime } } */

extern void abort (void);
int a[1024], b = -1;

int
main ()
{
  int i;
dummyMethod1();
  #pragma omp parallel for simd ordered
  for (i = 0; i < 1024; i++)
    {
      a[i] = i;
      #pragma omp ordered threads simd
      {
	if (b + 1 != i)
dummyMethod2();
	  abort ();
	b = i;
      }
      a[i] += 3;
    }
  if (b != 1023)
    abort ();
dummyMethod3();
  for (i = 0; i < 1024; i++)
    if (a[i] != i + 3)
      abort ();
  return 0;
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