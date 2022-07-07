#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
float A[1024];

int main()
{
  int i, j;
dummyMethod1();
  #pragma omp parallel for \
  schedule(runtime) private(j)
  for (i = 0; i < 1024; i++)
    for (j = 0; j < 5000000; j++)
      A[i] += j;
}
dummyMethod2();
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