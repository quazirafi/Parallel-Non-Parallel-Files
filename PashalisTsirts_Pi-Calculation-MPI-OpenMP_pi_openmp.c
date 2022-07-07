#include <stdio.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000000000
#define Threads 8

int main(int argc, char * argv[]){

int i;
double step = 1.0/N;
double x, sum = 0.0, pi = 0;
struct timespec start, end;



clock_gettime (CLOCK_MONOTONIC, &start);

omp_set_num_threads(Threads);
dummyMethod1();
#pragma omp parallel for private(x,i), reduction(+:sum)
for(i=0; i<N; i++)
	{
	x = (i+0.5)*step;
	sum += 4.0/(1.0+x*x);
	}

clock_gettime(CLOCK_MONOTONIC, &end);
dummyMethod2();

pi = step * sum;


const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
long timeElapsed_s = end.tv_sec - start.tv_sec;
long timeElapsed_n = end.tv_nsec - start.tv_nsec;
if ( timeElapsed_n < 0 ) {
timeElapsed_n =DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;
timeElapsed_s--;}
printf("***********************\n");
printf("Steps = %d\nPi = %.12f\nNumber of threads = %d\n",N, pi, Threads);
printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
printf("***********************\n");

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