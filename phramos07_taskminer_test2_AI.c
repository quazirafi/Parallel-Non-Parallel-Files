#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
void func(int a, int b, int *n) {
  for (int i = 0; i < b; i += 2) {
    n[i] = n[i] + 1;
  }
}

void funcA(int a, int b, int *n) {
  for (int i = 0; i < b; i++) {
    for (int j = 0; j < a; j++) {
      n[i * a + j] = i + j;
    }
  }
}

void funcB(int a, int b, int *m) {
  int i;
  for (i = 0; i < a; i++) {
    m[i * 4] = i;
  }
}

void funcC(int n, int *m) {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      m[i * n + j] = i;
}
*/
int main() {
  int pont[43], i;
  #pragma omp target data map(tofrom: pont[0:43])
  {
  #pragma omp target if(!RST_AI1)
			dummyMethod1();
  #pragma omp parallel for 
  for (i = 0; i <= 42; i++)
    pont[i] = 0;
			dummyMethod2();
  #pragma omp target if(!RST_AI1)
			dummyMethod1();
  #pragma omp parallel for 
  for (i = 0; i < 42; i++)
    pont[i] += 100;
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