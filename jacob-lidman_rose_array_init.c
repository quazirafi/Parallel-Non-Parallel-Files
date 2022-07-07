#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// Test the handling of two loops under omp for
// watch the loop index replacement (private by default)
int main(void)
{
  int i, j;
  float u[500][500];

dummyMethod1();
#pragma omp parallel for
  for (i=0; i<500; i++)
    for (j=0; j<500; j++)
    {
      u[i][j] = 0.0;
    }

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