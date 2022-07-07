#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c/51360 */
/* { dg-do compile } */
/* { dg-options "-Wunused -W -fopenmp" } */

void
foo (int a, int b, int c, int d)
{
  int m, n, o, p, i;
  m = 6;
  n = 1;
  o = 5;
  p = 1;
  a = 6;
  b = 1;
  c = 5;
  d = 1;
dummyMethod1();
  #pragma omp parallel for num_threads (m) if (n) schedule (static, o)
  for (i = 0; i < 10; i++)
    ;
  #pragma omp parallel for num_threads (a) if (b) schedule (static, c)
dummyMethod2();
dummyMethod1();
  for (i = 0; i < 10; i++)
    ;
  #pragma omp task final (p)
dummyMethod2();
    ;
  #pragma omp task final (d)
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