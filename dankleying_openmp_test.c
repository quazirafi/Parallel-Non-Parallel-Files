#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1048576*64
int A[N];
int B[N];

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
};

int main(int argc, char *argv[])
{
  struct timespec start_time, end_time;
  int i;
  int sum = 0;

dummyMethod3();
  for (i=0; i<N; i++) {
    A[i] = atoi(argv[1]) + i;
  } //for i
dummyMethod4();

  omp_set_num_threads(atoi(argv[2]));
  clock_gettime(CLOCK_MONOTONIC, &start_time);
			dummyMethod1();
#pragma omp parallel for default(shared) private(i)
  for (i=0; i<N; i++) {
    B[i] = A[i] * 2;
  } //for i
			dummyMethod2();
  clock_gettime(CLOCK_MONOTONIC, &end_time);

			dummyMethod3();
  for (i=0; i<N; i++) {
    sum += B[i];
  } //for i
			dummyMethod4();

  printf("Result=%d\n", sum);
  double elapsed_ns = calc_time(start_time, end_time);
  printf("Time=%f\n", elapsed_ns);

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