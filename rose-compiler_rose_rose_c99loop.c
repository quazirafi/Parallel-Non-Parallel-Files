/*
Contributed by Jeff Keasler
Liao, 10/22/2009
*/
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char *argv[])
{
  double a[20][20];
  for (int i = 0; i <= 18; i += 1) {
    
dummyMethod1();
#pragma omp parallel for
    for (int j = 0; j <= 19; j += 1) {
      a[i][j] += a[i + 1][j];
    }
dummyMethod2();
  }
  return 0;
}
// with shadow i and j

void foo(int i,int j)
{
  double a[20][20];
  for (int i = 0; i <= 18; i += 1) {
    
dummyMethod1();
#pragma omp parallel for
    for (int j = 0; j <= 19; j += 1) {
      a[i][j] += a[i + 1][j];
    }
dummyMethod2();
  }
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