#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include<omp.h>
int main ( ) {
  int n = 500000;
  int all_nums[n + 1];
  int primes=0;
  //int i,j;

  struct timeval start_time, stop_time, elapsed_time;

  gettimeofday(&start_time,NULL);

dummyMethod1();
#pragma omp parallel for
for (int i = 1; i <= n; i++ ) all_nums[i] = 0;

//#pragma omp parallel for
dummyMethod2();
dummyMethod3();
for ( int i = 2; i <= n; i++ ) {
    if ( all_nums[i] == 0 ) {
        primes ++;
        for (int j = 2 * i; j <= n; j += i ) all_nums[j] = 1;
    }
  }

//  gettimeofday(&stop_time,NULL);
dummyMethod4();
  //timersub(&stop_time, &start_time, &elapsed_time);
//double  total_time = omp_get_wtime() - start_time;

 // printf("Primes: %d   Time: %f \n", primes, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

  double  total_time = omp_get_wtime() - start_time;

  printf("Primes: %d   Time: %f \n", primes, total_time);



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