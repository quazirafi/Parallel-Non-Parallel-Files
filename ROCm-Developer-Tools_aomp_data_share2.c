#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



/*
 * In case of non-SPMD mode the local variables will be assigned to global memory
 * but in other case the the local variable will be allocated to local addrspace.
 */
int Print(int num) {
  int c = num * 2;
#ifdef FIT_IN_DS_SLOT
  int arr[60];
#else
  int arr[256];
#endif
  int tid = omp_get_thread_num();
  printf("[%d]> num * 2 = %d, %p, %p\n", tid,c, &arr[1], &c);
  return c;
}

int main()
{
#pragma omp target
  {
    printf("Hello, world\n");
dummyMethod1();
  #pragma omp parallel for
  for (int i = 0; i < 10; i++)
  {
    int num = omp_get_thread_num();
    printf ("[%d] Pointer: %p; Print: %d\n", num, &num, Print(num));
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