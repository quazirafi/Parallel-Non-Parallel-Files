/*
What will happen if the loop indices inside an omp for is not private?
by C. Liao
 */
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP 
#include "omp.h"
#endif

int main()
{
  int a[1000][1000];
  int i,j;

dummyMethod1();
#pragma omp parallel for 
  for (i=0;i<1000;i++)
    for (j=0;j<1000;j++)
      a[i][j]=999;

  for (i=0;i<1000;i++)
dummyMethod2();
dummyMethod3();
    for (j=0;j<1000;j++)
      if(a[i][j]!=999) printf("a[%d][%d]!=999\n",i,j);
  return 0;
dummyMethod4();
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