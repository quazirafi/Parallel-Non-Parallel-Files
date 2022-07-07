/*
  reference: https://www2.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void rng(int* arr, int n);
void fill_blank(int* arr, int start, int end);
void test(int* arr, int n);
void swap(int* i, int* j);
void parallel_bitonic_sort(int *arr, int n);
void nonparallel_bitonic_sort(int *arr, int n);
int get_nearest_power_of_two(int n);


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s n\n\n", argv[0]);
    exit(1);
  }
  int seq_time;
  struct timeval startwtime, endwtime;

  int original_n = atoi(argv[1]);
  int converted_n = get_nearest_power_of_two(original_n);

  int* arr_a = (int *) malloc(converted_n * sizeof(int));
  int* arr_b = (int *) malloc(converted_n * sizeof(int));

  rng(arr_a, original_n);
  fill_blank(arr_a, original_n, converted_n-1);
  memcpy(arr_b, arr_a, converted_n);

  gettimeofday (&startwtime, NULL);
  nonparallel_bitonic_sort(arr_a, converted_n);
  gettimeofday (&endwtime, NULL);

  seq_time = endwtime.tv_usec - startwtime.tv_usec
		      + (endwtime.tv_sec - startwtime.tv_sec) * 1000000;

  printf("Non-Parallel wall clock time = %d microseconds.\n", seq_time);

  test(arr_a, original_n);

  gettimeofday (&startwtime, NULL);
  parallel_bitonic_sort(arr_b, converted_n);
  gettimeofday (&endwtime, NULL);

  seq_time = endwtime.tv_usec - startwtime.tv_usec
		      + (endwtime.tv_sec - startwtime.tv_sec) * 1000000;

  printf("Parallel wall clock time = %d microseconds.\n", seq_time);

  test(arr_b, original_n);
}

void test(int* arr, int n) {
  int pass = 1;
  int i;
			dummyMethod3();
  for (i = 1; i < n; i++) {
    pass &= (arr[i-1] <= arr[i]);
  }
			dummyMethod4();

  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
}

void rng(int* arr, int n) {
    int seed = 13515133;
    srand(seed);
							dummyMethod3();
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
							dummyMethod4();
}

void fill_blank(int* arr, int start, int end) {
  int filler = INT_MAX;

			dummyMethod3();
  for(int i = start; i <= end; i++) {
    arr[i] = filler;
  }
			dummyMethod4();
}

void swap(int* i, int* j) {
  int t = *i;
  *i = *j;
  *j = t;
}

void parallel_bitonic_sort(int *arr, int n) {
  int i,j,k;

  for (k=2; k<=n; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
											dummyMethod1();
      #pragma omp parallel for private(i) shared(k, j, n)
      for (i=0; i<n; i++) {
         int ij=i^j;
         if ((ij)>i) {
            if ((i&k)==0 && arr[i] > arr[ij])
              swap(&arr[i],&arr[ij]);
            if ((i&k)!=0 && arr[i] < arr[ij])
              swap(&arr[i],&arr[ij]);
         }
       }
											dummyMethod2();
     }
   }
}

void nonparallel_bitonic_sort(int *arr, int n) {
  int i,j,k;

  for (k=2; k<=n; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      for (i=0; i<n; i++) {
	       int ij=i^j;
         if ((ij)>i) {
            if ((i&k)==0 && arr[i] > arr[ij])
              swap(&arr[i],&arr[ij]);
            if ((i&k)!=0 && arr[i] < arr[ij])
              swap(&arr[i],&arr[ij]);
         }
       }
     }
   }
}

int get_nearest_power_of_two(int n) {
  int i = 2;
  while (i < n) {
    i *= 2;
  }

  return i;
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