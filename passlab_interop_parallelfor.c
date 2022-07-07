#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
 * Combined parallel for
 * with multiple clauses
 * */
int main(void)
{
  int i, a[1000];
  int sum;
dummyMethod1();
#pragma omp parallel for if(1) ordered reduction(+:sum) schedule(dynamic, 5) 
  for (i=0;i<1000;i++)
  {
    a[i]=i*2;
    sum+=i;
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