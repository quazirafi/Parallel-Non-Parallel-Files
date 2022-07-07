#ifdef _OPENMP
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#endif #include <stdio.h>
#define N 16

void main(){
  int i, NumT, MyID;
  
  NumT = omp_get_num_threads();
  MyID = omp_get_thread_num();
  printf("S: I am %d/%d.¥n", MyID, NumT );
dummyMethod1();
  #pragma omp parallel for
  for( i = 0; i < N; i++ ){
    NumT = omp_get_num_threads();
    MyID = omp_get_thread_num();
    printf("P: i=%d, thread= %d/%d.¥n",i, MyID,NumT );
}
dummyMethod2();
  NumT = omp_get_num_threads();
  MyID = omp_get_thread_num();
  printf("S: I am %d/%d.¥n", MyID, NumT );
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