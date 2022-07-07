#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

int main(void)
{
  unsigned id = omp_loop_register("main-loop");

  omp_set_schedule(omp_sched_binlpt, 0);
  omp_set_num_threads(4);

  unsigned workload[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  omp_set_workload(id, workload, 16, true);
dummyMethod1();
#pragma omp parallel for schedule(runtime)
  for (size_t i = 0; i < 16; i++) {
    printf("Thread %i executing iteration %i (workload %u).\n",
           omp_get_thread_num(),
           i,
           workload[i]);
  }
dummyMethod2();

  printf("-----------------------------------------------------\n");

  unsigned workload2[16] = { 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1};
  omp_set_workload(id, workload2, 16, false);
dummyMethod1();
#pragma omp parallel for schedule(runtime)
  for (size_t i = 0; i < 16; i++) {
    printf("Thread %i executing iteration %i (workload %u).\n",
           omp_get_thread_num(),
           i,
           workload2[i]);
  }
dummyMethod2();

  printf("-----------------------------------------------------\n");

  omp_set_workload(id, workload2, 16, true);
			dummyMethod1();
#pragma omp parallel for schedule(runtime)
  for (size_t i = 0; i < 16; i++) {
    printf("Thread %i executing iteration %i (workload %u).\n",
           omp_get_thread_num(),
           i,
           workload2[i]);
  }
			dummyMethod2();

  omp_loop_unregister(id);

  return EXIT_SUCCESS;
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