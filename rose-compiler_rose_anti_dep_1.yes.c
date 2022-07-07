#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc,char *argv[])
{
  double a[20][20];

dummyMethod1();
#pragma omp parallel for 
  for (int i = 0; i <= 19 - 1; i += 1) {
    for (int j = 0; j <= 20 - 1; j += 1) {
      a[i][j] += a[i + 1][j];
    }
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