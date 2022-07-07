#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int N=100;
int b[100],c[100];
int j;

void foo()
{
dummyMethod1();
#pragma omp parallel for shared(b) firstprivate(c)
  for (j=0; j<N; j++)
  {   
    b[j] = c[j];
  }
dummyMethod2();
dummyMethod1();
#pragma omp parallel for shared(b) firstprivate(c)
  for (j=0; j<N; j++)
  {   
    b[j] = c[j];
  }
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