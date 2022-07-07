/* Test multiple reduction clauses with different reduction operations
 */
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 4

int main ()
{
 int i,total=1000000, yy=10000,zz=10000;
 double res=0.0;

 omp_set_num_threads(NUM_THREADS);

dummyMethod1();
 #pragma omp parallel for reduction(+:res) reduction(*:yy,zz)
 for (i=0; i<= total; i++){
  res = res + i;
  res = res - 2*i;
  yy *=1;
  zz*=1;
  }
 
 printf("the sum of 1000000 is :%.0f\n", res);
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