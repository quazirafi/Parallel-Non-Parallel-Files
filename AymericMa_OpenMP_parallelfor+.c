#include <stdio.h>
#include "omp_repair.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 20
int main() {
  int a[SIZE], b[SIZE], c[SIZE], i, tid;
dummyMethod3();
  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = 2 * i;
  }
dummyMethod4();
dummyMethod1();
  #pragma omp parallel for shared(a, b, c) private(i, tid)
/* ajout des clauses directement au pragma et retrait du bloc {}*/
    for(i = 0; i < SIZE; i++) {
      c[i] = a[i] + b[i];
      tid = omp_get_thread_num();
      printf("Thread %d, i = %d\n", tid, i);
    }
dummyMethod2();

dummyMethod3();
  for(i = 0; i < SIZE; i++) printf("%d\n", c[i]);
}
dummyMethod4();
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