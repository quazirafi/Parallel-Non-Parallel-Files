#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
  
  int sum = 0, N = 10;
  int i;
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
    for(i=0; i<N; i++) {
      sum++;
    }
dummyMethod2();
    printf("%d\n", sum);
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