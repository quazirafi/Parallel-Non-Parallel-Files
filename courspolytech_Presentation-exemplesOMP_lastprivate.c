#include <stdio.h>
#include "omp_repair.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 20
int main() {
  int i,a, n=SIZE;
dummyMethod1();
#pragma omp parallel for private(i) lastprivate(a)
  for (i=0; i<n; i++)
  {
    a = i+1;
    printf("Thread %d a = %d i = %d\n", omp_get_thread_num(),a,i);
  }
dummyMethod2();
printf("Value of a after parallel for: a = %d\n",a);
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