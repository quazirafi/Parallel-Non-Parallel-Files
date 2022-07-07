#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
# include <stdlib.h>
# include <stdio.h>
# include <omp.h>
# include <sys/time.h>

int main ( ){

  int n = 500000;
  int not_primes=0;
  int i,j;

//  double  start_time = omp_get_wtime();
  struct timeval start_time, stop_time, elapsed_time;
  gettimeofday(&start_time,NULL);

dummyMethod1();
#pragma omp parallel for private(j) reduction(+: not_primes) schedule(dynamic) 
  for ( i = 2; i <= n; i++ ){
    for ( j = 2; j < i; j++ ){
      if ( i % j == 0 ){
	not_primes++;
dummyMethod2();
	break;
      }
    }
  }

  //double  total_time = omp_get_wtime() - start_time;
  //printf("Primes: %d   Time: %f \n", n - not_primes -1, total_time);
  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time);
  printf("Primes: %d   Time: %f \n", n-not_primes-1, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

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