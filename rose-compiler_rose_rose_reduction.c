/*
 *  Test for automatic recognition of reduction variables
 * */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int a[100];
int sum;

void foo()
{
  int i;
  int sum2;
  int xx;
  int yy;
  int zz;
  sum = 0;
  
dummyMethod1();
#pragma omp parallel for private (i) reduction (+:sum,xx) reduction (-:yy) reduction (*:zz)
  for (i = 0; i <= 99; i += 1) {
    a[i] = i;
    sum = a[i] + sum;
    xx++;
    yy--;
    zz *= a[i];
  }
dummyMethod2();
  sum2 = sum + xx + yy + zz;
  a[1] = 1;
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