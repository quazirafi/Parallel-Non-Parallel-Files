#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/27388 */
/* { dg-do compile } */
/* { dg-options "-fopenmp -fdump-tree-omplower" } */

extern void baz (int);

void
foo (void)
{
  int i;
dummyMethod1();
#pragma omp parallel for shared (i)
  for (i = 0; i < 2; i++)
    baz (i);
}
dummyMethod2();

void
bar (void)
{
  int j = 0;
#pragma omp parallel shared (j)
  {
    j++;
#pragma omp for
dummyMethod3();
    for (j = 0; j < 2; j++)
      baz (j);
  }
dummyMethod4();
}

/* { dg-final { scan-tree-dump-times "shared\\\(i\\\)\[^\\n\]*private\\\(i\\\)" 0 "omplower" } } */
/* { dg-final { scan-tree-dump-times "private\\\(i\\\)\[^\\n\]*shared\\\(i\\\)" 0 "omplower" } } */
/* { dg-final { scan-tree-dump-times "omp for\[^\\n\]*private\\\(i\\\)" 1 "omplower" } } */
/* { dg-final { scan-tree-dump-times "shared\\\(j\\\)\[^\\n\]*private\\\(j\\\)" 0 "omplower" } } */
/* { dg-final { scan-tree-dump-times "private\\\(j\\\)\[^\\n\]*shared\\\(j\\\)" 0 "omplower" } } */
/* { dg-final { scan-tree-dump-times "omp for\[^\\n\]*private\\\(j\\\)" 1 "omplower" } } */
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