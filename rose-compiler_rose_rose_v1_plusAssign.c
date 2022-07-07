#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char *argv[])
{
  int i;
  int j;
  double a[20][20];
// memset(a,0,(sizeof(a)));
  for (i = 0; i <= 18; i += 1) {
    
dummyMethod1();
#pragma omp parallel for private (j)
    for (j = 0; j <= 19; j += 1) {
      a[i][j] += a[i + 1][j];
    }
dummyMethod2();
  }
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