#include <math.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 30000000

double gtod_timer(void);    // timer prototype
int c_setaffinity(int);     // affinity prototype

int main() {

  int i, nt=1, niter=0;
  double a[N], error=0.0, sum;

  double time, t0, t1;

#ifdef _OPENMP
#pragma omp parallel private(nt)
{ nt = omp_get_num_threads(); if(nt<1) printf("NO print, OMP warmup.\n"); }
#endif

dummyMethod3();
  for(i = 0; i < N-1; i+=2) {a[i]   = 0.0; a[i+1] = 1.0;}
  //#ifdef _OPENMP
dummyMethod4();
  //#pragma omp parallel for private(i)
  //for(i = 0; i < N-1; i+=2) {a[i]   = 0.0; a[i+1] = 1.0;}
  //#endif

  t0 = gtod_timer();
    
  do {
    #ifdef _OPENMP
dummyMethod1();
    #pragma omp parallel for schedule(runtime) private(i)
    for (i = 1; i < N;   i+=2) a[i] = (a[i] + a[i-1]) / 2.0;
    #pragma omp parallel for schedule(runtime)
dummyMethod2();
							dummyMethod1();
    for (i = 0; i < N-1; i+=2) a[i] = (a[i] + a[i+1]) / 2.0;
							dummyMethod2();
    #endif
      
    error=0.0; niter++;
    #ifdef _OPENMP
							dummyMethod1();
    #pragma omp parallel for schedule(runtime) private(i) reduction(+:error) 
    for (i = 0; i < N-1; i++) error = error + fabs(a[i] - a[i+1]);
							dummyMethod2();
    #endif
  } while (error >= 1.0);

  t1 = gtod_timer();
  time  = t1 - t0;

  printf("%lf\n",time);
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