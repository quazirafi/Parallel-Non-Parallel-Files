#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

#define N       50
#define CHUNKSIZE   5

int
main ()
{
  int i, chunk;
  float c[N];

  chunk = CHUNKSIZE;
dummyMethod1();
#pragma omp parallel for shared (c, chunk) schedule (dynamic, chunk)
  for (i = 0; i < N; i++)
    c[i] = i;

  return 0;
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