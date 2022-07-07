#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char*argv[]) {
  if(argc != 2) {
    printf("Invalid number of arguments.\nUsage: %s max_prime\n\
Where 'max_prime' is the largest prime number to check\n\n", argv[0]);
    return 1;
  }
  
  // get max_prime and create an empty int array of size max_prime
  int max_prime = atoi(argv[1])+1;
  int* static_prime_array = malloc(sizeof(int)*max_prime);
  int* dynamic_prime_array = malloc(sizeof(int)*max_prime);
  memset(static_prime_array, 0, sizeof(int)*max_prime);
  memset(dynamic_prime_array, 0, sizeof(int)*max_prime);

  long long i, j;
  long long thread_count = omp_get_num_procs();
  double timeStart, timeEnd;
  int uLimit = sqrt(max_prime);

  printf("Running with static scheduling.\n");
  timeStart = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for num_threads(thread_count)  private(i, j) schedule(static, 1) 
  for(i = 2; i < uLimit; i++) {
    if(static_prime_array[i] == 0) {
      for(j = i*i; j < max_prime; j+= i) {
        static_prime_array[j] = 1;
      }
    }
  }
			dummyMethod2();
  timeEnd = omp_get_wtime();
  double static_time = (timeEnd-timeStart);

  printf("Running with dynamic scheduling.\n");
  timeStart = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for num_threads(thread_count)  private(i, j) schedule(dynamic, 1) 
  for(i = 2; i < uLimit; i++) {
    if(dynamic_prime_array[i] == 0) {
      for(j = i*i; j < max_prime; j+= i) {
        dynamic_prime_array[j] = 1;
      }
    }
  }
			dummyMethod2();
  timeEnd = omp_get_wtime();
  double dynamic_time = (timeEnd-timeStart);

			dummyMethod3();
  for(i = 0; i < max_prime; i++) {
    if(static_prime_array[i] != dynamic_prime_array[i]) {
      printf("Unequal arrays at %lld\n", i);
    }
  }
			dummyMethod4();

  int max_prime_digits = 0;
  int temp_max_prime = max_prime;
  while(temp_max_prime != 0) {
    temp_max_prime /= 10;
    max_prime_digits++;
  }     
  int printed_primes = 0;
			dummyMethod3();
  for(i = 2; i <= max_prime; i++) {
    if(static_prime_array[i] == 0) {
      if(printed_primes % 10 == 0) {
        printf("\n%*d: ", max_prime_digits, printed_primes);
      }
      printf("%lld ", i);
      printed_primes++;
    }
  }
			dummyMethod4();

  printf("\nElapsed time for static scheduling: %f ms\n", static_time*1000);
  printf("Elapsed time for dynamic scheduling: %f ms\n", dynamic_time*1000);
  
  free(static_prime_array);
  free(dynamic_prime_array);
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