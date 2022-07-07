#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#pragma omp declare target
void hostrpc_fptr0(void* fun_ptr);
#pragma omp end declare target

//  A host function will synchronously call from a device as a function pointer
void myfun() {
  fprintf(stderr, " This is myfun writing to stderr \n");
}
int main()
{
  int N = 10;

  int a[N];
  int b[N];

  int i;

dummyMethod3();
  for (i=0; i<N; i++){
    a[i]=0;
    b[i]=i;
  }
dummyMethod4();
  //void (*fun_ptr)(int) = &myfun;
  void (*fun_ptr)() = &myfun;
  
  printf("Testing myfun execution as a function pointer \n");
  (*fun_ptr)();

  printf("Testing myfun execution from device using hostrpc_fptr0\n");
			dummyMethod1();
  #pragma omp target parallel for map(from: a[0:N]) map(to: b[0:N]) is_device_ptr(fun_ptr)
  for (int j = 0; j< N; j++) {
    a[j]=b[j];
    hostrpc_fptr0(fun_ptr);
  }
			dummyMethod2();

  printf("Testing the host fallback of hostrpc_fptr0 \n");
  hostrpc_fptr0(fun_ptr);

  int rc = 0;
			dummyMethod3();
  for (i=0; i<N; i++)
    if (a[i] != b[i] ) {
      rc++;
      printf ("Wrong value: a[%d]=%d\n", i, a[i]);
    }
			dummyMethod4();

  if (!rc){
    printf("Success\n");
    return EXIT_SUCCESS;
  } else{
    printf("Failure\n");
    return EXIT_FAILURE;
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