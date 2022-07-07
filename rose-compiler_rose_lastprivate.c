#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define n 100
int a[n];
int main()
{
  int i,j;
  j = 0;
dummyMethod1();
#pragma omp parallel for lastprivate(j)
  for(i=1; i<=n; i++){
      j = j + 1;
    a[i] = a[i] + j;
  }
dummyMethod2();
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