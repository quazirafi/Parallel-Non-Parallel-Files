// Declared in a scope inside the construct: private by default
// but if static storage: it is shared
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char* argv[])
{
  int i;
  int len=100;
  int a[100];

dummyMethod3();
  for (i=0;i<len;i++)
    a[i]=i;

#pragma omp parallel for
dummyMethod4();
dummyMethod1();
  for (i=0;i<len;i++)
  {
    static int tmp = 0;
    tmp = a[i]+i;
    a[i] = tmp;
  }
dummyMethod2();

  printf("a[50]=%d\n", a[50]);
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