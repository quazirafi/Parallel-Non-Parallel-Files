#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char **argv) {
  int a[4] = {1,2,3,4};
  int b[4] = {1,1,1,1};

  for (int i = 0; i < 1; ++i) {
    if (i < 2) {
dummyMethod1();
      return -1;
    }
  }

#pragma omp parallel for
  for (int i = 0; i < 4; ++i) {
dummyMethod1();
    a[i] = 3*a[i];
#pragma omp parallel for
dummyMethod2();
    for(int j = 0; j < 4; ++j) {
      b[j] = b[j] + a[i];
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