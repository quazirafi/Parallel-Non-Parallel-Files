/*
 * dependence graph:
 */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo()
{
  int i;
  int x;
  int a[100];
  
dummyMethod1();
#pragma omp parallel for private (i)
  for (i = 0; i <= 99; i += 1) {
    a[i] = a[i] + 1;
  }
dummyMethod2();
}
/*
  non loop carried anti dependence for array accesses  : level =1 > 0 
dep SgExprStatement:a[i] =((a[i]) + 1); SgExprStatement:a[i] =((a[i]) + 1); 1*1 ANTI_DEP; commonlevel = 1 CarryLevel = 1  Is precise SgPntrArrRefExp:(a[i])@10:11->SgPntrArrRefExp:a[i]@10:9 == 0;||::
 */
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