#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int foo (void)
{
  int i, a;

  a = 30;

dummyMethod1();
  #pragma omp parallel for lastprivate (a)
  for (i = 0; i < 10; i++)
    a = a + i;

  return a;
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