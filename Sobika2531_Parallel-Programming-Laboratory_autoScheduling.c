#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void schedule_auto()
{
  int N = 20;
  int i;
  double avg = 0;

  omp_set_num_threads(4);

dummyMethod1();
  #pragma omp parallel for reduction(+:avg) schedule(auto)
  for (i = 0; i < N; ++i) 
  {
    avg += i;
    printf("Thread %d executing iteration %d\n",omp_get_thread_num(),i);
  }
dummyMethod2();

  avg /= N;
  printf("average is %.4f\n",avg);
}

int main()
{
  printf("I'm from auto scheduling\n\n");
  schedule_auto();

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