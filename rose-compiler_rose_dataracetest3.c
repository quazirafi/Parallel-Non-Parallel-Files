#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// data race EXISTS

int main() {
  double a[10][10];
  for(int d=0;d<1;d++) {
    int j;
dummyMethod1();
#pragma omp parallel for private(j)
    for(int i=0;i<10;i++) {
      for(j=0;j<10;j++) {
        a[i][j]=0;
#pragma ivdep
dummyMethod2();
#pragma vector always
#pragma simd
        for(int k=0;k<10;k++) {
          a[j][k]=1;
        }
      }
    }
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