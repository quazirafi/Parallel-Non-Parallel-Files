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
  float red,black;
  double time, t0, t1;

#ifdef _OPENMP
#pragma omp parallel private(nt)
{ nt = omp_get_num_threads(); if(nt<1) printf("NO print, OMP warmup.\n"); }
#endif

   #ifdef _OPENMP
dummyMethod1();
   #pragma omp parallel for private(i)
   for(i = 0; i < N-1; i+=2) {a[i]   = 0.0; a[i+1] = 1.0;}
   #endif    
dummyMethod2();

   t0 = gtod_timer();
   
   #pragma omp parallel shared(error,red,black) 
   {
   do {

      #pragma omp single
      {
	//inital varaibles
      	red = (a[1]+a[0])/2;
      	black = (red+a[1])/2;
      }; 
      #pragma omp for schedule(runtime) 
											dummyMethod3();
      for (i = 1; i < N;   i+=2) 
      {
	//offsetting by initial variables
      	a[i] = (a[i] + red) / 2.0;
	a[i] = (black + a[i+1]) / 2.0;
      } 
											dummyMethod4();
      //initializing error by one thread since error is shared	
      #pragma omp single
      {
      	error=0.0; niter++;
      }; 
      #pragma omp for schedule(runtime) reduction(+:error)
											dummyMethod4();
											dummyMethod3();
      for (i = 0; i < N-1; i++) error = error + fabs(a[i] - a[i+1]);
      
   } while (error >= 1.0);
 };
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