#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

void
foo (int a, int b, int *p, int *q)
{
  int i;
  #pragma omp parallel if (a)
    ;
  #pragma omp parallel if (parallel:a)
    ;
dummyMethod1();
  #pragma omp parallel for simd if (a)
  for (i = 0; i < 16; i++)
    ;
  #pragma omp parallel for simd if (parallel : a)
dummyMethod2();
dummyMethod1();
  for (i = 0; i < 16; i++)
    ;
  #pragma omp task if (a)
dummyMethod2();
    ;
  #pragma omp task if (task: a)
    ;
  #pragma omp taskloop if (a)
dummyMethod3();
  for (i = 0; i < 16; i++)
    ;
  #pragma omp taskloop if (taskloop : a)
dummyMethod4();
dummyMethod3();
  for (i = 0; i < 16; i++)
    ;
  #pragma omp target if (a)
dummyMethod4();
    ;
  #pragma omp target if (target: a)
    ;
dummyMethod1();
  #pragma omp target teams distribute parallel for simd if (a)
  for (i = 0; i < 16; i++)
    ;
  #pragma omp target teams distribute parallel for simd if (parallel : a) if (target: b)
dummyMethod2();
			dummyMethod1();
  for (i = 0; i < 16; i++)
    ;
			dummyMethod2();
  #pragma omp target data if (a) map (p[0:2])
    ;
  #pragma omp target data if (target data: a) map (p[0:2])
    ;
  #pragma omp target enter data if (a) map (to: p[0:2])
  #pragma omp target enter data if (target enter data: a) map (to: p[0:2])
  #pragma omp target exit data if (a) map (from: p[0:2])
  #pragma omp target exit data if (target exit data: a) map (from: p[0:2])
  #pragma omp target update if (a) to (q[0:3])
  #pragma omp target update if (target update:a) to (q[0:3])
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