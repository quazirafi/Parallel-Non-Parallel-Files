#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_ITS 10000

int main()
{
  int nproc, i, sum, thread_id;
  nproc = omp_get_max_threads();
  int its_per_proc[nproc];

dummyMethod3();
  for (i = 0; i< nproc; ++i){
    its_per_proc[i] = 0;
  }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for private(thread_id)
  for (i = 0; i< MAX_ITS; ++i){
    thread_id = omp_get_thread_num();
    its_per_proc[thread_id]++;
}
dummyMethod2();

  sum = 0;
dummyMethod3();
  for (i = 0; i< nproc; ++i){
    printf("Processor %i performed %i iterations\n", i, its_per_proc[i]);
    sum += its_per_proc[i];
  }
dummyMethod4();
  printf("Total work on all processors is %i\n", sum); 
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