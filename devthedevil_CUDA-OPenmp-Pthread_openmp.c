#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "omp.h"
#include <math.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const double PI = 3.1415926535897932;
const long STEP_NUM = 1070596096;
const double STEP_LENGTH = 1.0 / 1070596096;

int main()
{
  struct timeval startTime;
  gettimeofday(&startTime, NULL);

  double sum = 0.0;
  double pi, x;

  printf("\nStart calculating...\n");
  // computational steps
dummyMethod1();
  #pragma omp parallel for reduction(+:sum) private(x) num_threads(16)
  for(int i = 0;i < STEP_NUM; i++)
  {
    x = (i + 0.5) * STEP_LENGTH;
    sum += 1.0 / (1.0 + x * x);
  }
dummyMethod2();
  pi = STEP_LENGTH * sum * 4;

  struct timeval endTime;
  gettimeofday(&endTime, NULL);
  printf("PI = %.16lf with error %.16lf\nTime elapsed : %lf seconds.\n\n", pi, fabs(pi - PI), (endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec) / 10E6 ));
  assert(fabs(PI - pi) <= 0.001);
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