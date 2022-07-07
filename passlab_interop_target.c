#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char* argv[])
{
  int i;
  int len = 1000;

  int a[1000];

dummyMethod3();
  for (i=0; i<len; i++)
    a[i]= i;

#pragma omp target if(target:test)
dummyMethod4();
dummyMethod1();
#pragma omp parallel for
  for (i=0;i< len -1 ;i++)
    a[i]=a[i]+1;

  return 0;
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