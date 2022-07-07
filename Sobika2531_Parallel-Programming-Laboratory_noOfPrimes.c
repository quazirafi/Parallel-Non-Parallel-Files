#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define B 10000000000L;

static int is_prime(long n)
{
  if(n == 0) 
    return 0;
  
  else if(n == 1) 
    return 0;
  
  else if(n == 2) 
    return 1;
  
  int temp = (int)(sqrt((double)n));
  int i;
  
dummyMethod3();
  for(i=2;i<=temp;i++)
    if(n%i==0)
      return 0;

  return 1;
dummyMethod4();
}

int main() 
{
  long n  = 100000000;
  int numprimes = 0;
  struct timespec start, end;
  
  clock_gettime(CLOCK_REALTIME,&start);
  
			dummyMethod1();
  #pragma omp parallel forschedule(dynamic, 1) reduction(+:numprimes) 
  for(long i = 1; i <= n; i++) 
  {
    if(is_prime(i) == 1)
      numprimes ++;
  }
			dummyMethod2();
  
  clock_gettime(CLOCK_REALTIME,&end);
  
  double accum=(end.tv_sec-start.tv_sec)+(double)(end.tv_nsec-start.tv_nsec)/B;
  printf("time = %f\n",accum);
  printf("Number of prime within %d: %d\n", n, numprimes);
  
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