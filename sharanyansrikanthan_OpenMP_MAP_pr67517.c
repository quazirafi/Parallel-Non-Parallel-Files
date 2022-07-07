#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/67517 */
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

int
foo (int x, int y, int z)
{
  int i;
dummyMethod1();
  #pragma omp parallel for simd linear (y : x & 15) linear (x : 16) linear (z : x & 15)
  for (i = 0; i < 256; ++i)
    x += 16, y += x & 15, z += x & 15;
  return x + y + z;
dummyMethod2();
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