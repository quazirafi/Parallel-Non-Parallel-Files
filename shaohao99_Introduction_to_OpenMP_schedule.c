#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void)
{

  int i,j,n=16;

dummyMethod1();
  #pragma omp parallel for default(none) schedule(runtime) private(i,j) shared(n)
//  #pragma omp parallel for default(none) schedule(static,2) private(i,j) shared(n)
  for (i=0; i<n; i++){
      printf("Iteration %d executed by thread %d\n", i, omp_get_thread_num());
      for (j=0; j<i; j++)   system("sleep 0.5");
  } 
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