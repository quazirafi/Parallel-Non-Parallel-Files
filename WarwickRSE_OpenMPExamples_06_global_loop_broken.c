/*THIS PROGRAM DOESN'T WORK PROPERLY*/

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
#pragma omp parallel for
  for (i=0;i<MAX_ITS;++i){
    /*Two threads trying to update this simultaneously won't work properly
    because updating the variable isn't instantaneous*/
    its_global++;
  }
dummyMethod2();

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