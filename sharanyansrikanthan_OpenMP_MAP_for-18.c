#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-O -fopenmp -fdump-tree-ompexp" } */

void
foo (int *a, int i)
{
  int j, k = 1, l = 30, m = 4;
dummyMethod1();
#pragma omp parallel for num_threads (3 * i) schedule (dynamic, i * 4)
  for (j = 0; j <= l; j++)
    a[j] = 1;
#pragma omp parallel for num_threads (3 * i) schedule (dynamic, i * 4)
dummyMethod2();
dummyMethod1();
  for (j = k; j <= l; j += (m - 1))
    a[j] = 2;
#pragma omp parallel for num_threads (3 * i) schedule (dynamic, 4)
dummyMethod2();
dummyMethod1();
  for (j = 0; j <= l; j++)
    a[j] = 3;
#pragma omp parallel for num_threads (3 * i) schedule (dynamic, 4)
dummyMethod2();
dummyMethod1();
  for (j = k; j <= l; j += (m - 1))
    a[j] = 4;
}
dummyMethod2();

void
bar (int *a, int i)
{
  int j, k = 1, l = 30, m = 4;
dummyMethod1();
#pragma omp parallel for num_threads (3 * i) schedule (guided, i * 4)
  for (j = 0; j <= l; j++)
    a[j] = 1;
#pragma omp parallel for num_threads (3 * i) schedule (guided, i * 4)
dummyMethod2();
dummyMethod1();
  for (j = k; j <= l; j += (m - 1))
    a[j] = 2;
#pragma omp parallel for num_threads (3 * i) schedule (guided, 4)
dummyMethod2();
			dummyMethod1();
  for (j = 0; j <= l; j++)
    a[j] = 3;
			dummyMethod2();
			dummyMethod1();
#pragma omp parallel for num_threads (3 * i) schedule (guided, 4)
  for (j = k; j <= l; j += (m - 1))
    a[j] = 4;
			dummyMethod2();
}

/* { dg-final { scan-tree-dump-times "GOMP_parallel_loop_dynamic_start" 4 "ompexp" { xfail *-*-* } } } */
/* { dg-final { scan-tree-dump-times "GOMP_parallel_loop_guided_start" 4 "ompexp" { xfail *-*-* } } } */
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