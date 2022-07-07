#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
  int c, i, chunk = 10;
  const int N = atoi(argv[1]); // iterations
  const int SIZE = atoi(argv[2]);
  omp_set_dynamic(0);
  int iCPU = omp_get_num_procs();
  omp_set_num_threads(iCPU);
  float a[SIZE], b[SIZE], result;
  
  for (c = 0; c < N; c++) {
    result = 0.0;
    for (i=0; i < SIZE; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }
dummyMethod1();
    #pragma omp parallel for      \
        default(shared) private(i)  \
        schedule(static,chunk)      \
        reduction(+:result)

      for (i=0; i < SIZE; i++)
          result += (a[i] * b[i]);
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