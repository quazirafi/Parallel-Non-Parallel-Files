#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_ITS 10000

int main(){

  int its_global, i;
  
  its_global = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:its_global)
  for (i=0;i<MAX_ITS;++i){
  /*Reduction means that its_global is recorded separately
dummyMethod2();
   on each thread and then combined between all threads by using
   a reduction operator (here +) at the end*/
    its_global++;
  }

  printf("Counter records %i iterations\n", its_global);
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