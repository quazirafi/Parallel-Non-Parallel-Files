#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// PR 24703
// { dg-do compile }

void work(int);
int work_param;
int sphinx_omp_thread_count;
int schedule_loop_cap;

int measure_omp_parallel_for_dynamic (void)
{
  int j;

dummyMethod1();
#pragma omp parallel for schedule(dynamic)
  for(j=0; j < sphinx_omp_thread_count * schedule_loop_cap; j++)
    work(work_param);

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