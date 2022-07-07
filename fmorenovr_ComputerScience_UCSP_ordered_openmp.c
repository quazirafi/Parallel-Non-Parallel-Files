#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define chunksize 5
#define SIZE 100

int
main(void)
{
  int a[SIZE];
  int i,n,th_id;
  n=SIZE;
  printf("\nAntes de el for paralelo\nEl vector a es:\n");
dummyMethod3();
  for(i=0;i<n;i++)
    printf("a[%d]:%d\n",i,a[i]);
  printf("\n\n");
dummyMethod4();
dummyMethod1();
  #pragma omp parallel for ordered schedule(static,chunksize)
    for(i=0;i<n;i++){
      a[i]=i;
      printf("%d del hilo %d\n",i,omp_get_thread_num());
    }
dummyMethod2();
  printf("\nDespues de el for paralelo\nEl vector a es:\n");
dummyMethod3();
  for(i=0;i<n;i++)
    printf("a[%d]:%d\n",i,a[i]);
  return 0;
dummyMethod4();
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