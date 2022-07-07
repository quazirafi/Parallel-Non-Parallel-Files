#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000
#define M 2000
#define B 1000000000.0

int main(void)
{
  int a[N][M];
  int i;
  int count=0;
  
dummyMethod3();
  for(i = 0; i < N; i++) 
  {
    for(int j=0;j<M;j++)
    {
      a[i][j]=rand()%100;
    }
  }
dummyMethod4();
  
  struct timespec start,end; 
  clock_gettime(CLOCK_REALTIME,&start);
  
			dummyMethod1();
  #pragma omp parallel for
  for(i = 0; i < N; i++) 
  {
    for(int j=0;j<M;j++)
    {
      if(a[i][j]>50)
      {
        count++;
      }
    }
  }
			dummyMethod2();
  
  clock_gettime(CLOCK_REALTIME,&end);
  
  double time=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/B;
  printf("number of elements greater than 50 is %d\n",count);
  printf("time taken to execute the code %f\n",time);
  
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