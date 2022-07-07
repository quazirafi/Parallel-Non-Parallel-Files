/* 
 * Scalar-to-scalar dependencies
 * */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int a[100];

void foo2()
{
  int i;
  int tmp;
  
dummyMethod1();
#pragma omp parallel for private (tmp,i)
  for (i = 0; i <= 99; i += 1) {
    tmp = a[i] + i;
    a[i] = tmp;
  }
dummyMethod2();
}

void foo()
{
  int i;
  int tmp;
  
dummyMethod1();
#pragma omp parallel for private (i) lastprivate (tmp)
  for (i = 0; i <= 99; i += 1) {
    tmp = a[i] + i;
    a[i] = tmp;
  }
dummyMethod2();
  i = tmp;
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