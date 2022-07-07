#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp -fdump-tree-omplower" } */

/* Test that we adjust pointer offsets for sink variables
   correctly.  */

typedef struct {
    char stuff[400];
} foo;

void
funk (foo *begin, foo *end)
{
  foo *p;
dummyMethod1();
#pragma omp parallel for ordered(1)
  for (p=end; p > begin; p--)
    {
#pragma omp ordered depend(sink:p+1)
dummyMethod2();
      void bar ();
        bar();
#pragma omp ordered depend(source)
    }
}

/* { dg-final { scan-tree-dump-times "depend\\(sink:p\\+400\\)" 1 "omplower" } } */
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