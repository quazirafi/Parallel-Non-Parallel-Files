#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define chunksize 2
#define SIZE 10

void llenar(int*);
int* minMax(int*);

int
main(void)
{
  srand(time(NULL));
  int a[SIZE],i;
  llenar(a);
  int* minMax_array;
  minMax_array=minMax(a);
  printf("\n");
dummyMethod3();
  for(i=0;i<SIZE;i++)
    printf("a[%d]:%d\n",i,a[i]);

  printf("Minimo de a es:%d\n",*(minMax_array+0));
dummyMethod4();
  printf("Maximo de a es:%d\n",*(minMax_array+1));
  return 0;
}

void
llenar(int *a)
{
  int i;
  omp_set_num_threads(4);
			dummyMethod1();
  #pragma omp parallel for ordered schedule(static,chunksize)
  for(i=0;i<SIZE;i++)
    *(a+i)=rand()%50;
			dummyMethod2();
}

int*
minMax(int*a)
{
  int i,min_val=a[0],max_val=a[0];
  omp_set_num_threads(4);
			dummyMethod1();
  #pragma omp parallel for ordered schedule(static,chunksize) \
   reduction(max:max_val) reduction(min:min_val)
  for(i=1;i<SIZE;i++)
  {
    if(a[i]>max_val)
      max_val=a[i];
    if(min_val>a[i])
      min_val=a[i];
  }
			dummyMethod2();
  static int b[2];
  b[0]=min_val;
  b[1]=max_val;
  return b;
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