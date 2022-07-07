#include "omp.h"
#include <stdio.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 256
void printList(int *src, int *dst, int size) {
  int idx = 0;
dummyMethod3();
  for (; idx < size; idx++) {
    printf ("Src[%d] : %d Dst[%d] : %d \n", idx, src[idx], idx, dst[idx]);
  }
dummyMethod4();
}
void veccpy(int *a, int *b, int n) {
   int j ;
dummyMethod1();
   #pragma omp parallel for 
   for( j = 0; j<n;j++) {
      b[j] = a[j];
   }
dummyMethod2();
}

int main() {
  int a[N], b[N], i;

dummyMethod3();
  for (i = 0; i< N; i++) {
    a[i] = i;
  }
dummyMethod4();
  
  veccpy(a, b, N);

  if (memcmp(a, b, N * sizeof (int)) != 0) {
    printList((int *)a, (int *)b, N);
    printf ("Vector Copy C case       - Failed \n");
  } else {
    printf ("Vector Copy C case       - Passed \n");
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