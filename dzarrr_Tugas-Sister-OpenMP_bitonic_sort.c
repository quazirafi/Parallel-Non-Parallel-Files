#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct timeval startwtime, endwtime;
double seq_time;


int N;          // data array size
int *a;         // data array to be sorted

const int ASCENDING  = 1;
const int DESCENDING = 0;


void test(void);
inline void exchange(int i, int j);
void compare(int i, int j, int dir);
void impBitonicSort(int paddedN);
void impBitonicSortParallel(int paddedN);
void rng(int* arr, int n);
int getPaddedN(int N);
int findMax(int* arr, int N);

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s n\n  where n is problem size (power of two)\n", argv[0]);
    exit(1);
  }

  N = atoi(argv[1]);

  int paddedN = getPaddedN(N);

  a = (int *) malloc(paddedN * sizeof(int));

  rng(a, N);

  //Output file input.txt
  FILE *finput ;
  finput = fopen("output/input.txt", "w");
			dummyMethod3();
  for(int i=0; i<N; i++) {
    fprintf(finput,"%d\n",a[i]);
  }
			dummyMethod4();
  fclose(finput);

  //Nambah data
  int maxNum = findMax(a, N);
			dummyMethod3();
  for (int i = N; i < paddedN; i++){
    a[i] = maxNum;
  }
			dummyMethod4();

  //Paralel Sort
  gettimeofday (&startwtime, NULL);
  impBitonicSortParallel(paddedN);
  gettimeofday (&endwtime, NULL);

  //Output file output.txt
  FILE *foutput ;
  foutput = fopen("output/output.txt", "w");
			dummyMethod3();
  for(int i=0; i<N; i++) {
    fprintf(foutput,"%d\n",a[i]);
  }
			dummyMethod4();
  fclose(foutput);

  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);

  printf("Parallel imperative wall clock time = %f\n", seq_time);
  test();

  rng(a, N);
  gettimeofday (&startwtime, NULL);
  impBitonicSort(paddedN);
  gettimeofday (&endwtime, NULL);

  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);

  printf("Serial imperative wall clock time = %f\n", seq_time);
  test();

  //print();
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
void test() {
  int pass = 1;
  int i;
			dummyMethod3();
  for (i = 1; i < N; i++) {
    pass &= (a[i-1] <= a[i]);
  }
			dummyMethod4();

  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
}

void rng(int* arr, int n) {
    int seed = 13515007; // Ganti dengan NIM anda sebagai seed.
    srand(seed);
							dummyMethod3();
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
							dummyMethod4();
}


inline void exchange(int i, int j) {
  int t;
  t = a[i];
  a[i] = a[j];
  a[j] = t;
}

int getPaddedN(int N){
  int duaPangkat = 1;
  while (duaPangkat < N) {
    duaPangkat *= 2;
  }
  return duaPangkat;
}


void compare(int i, int j, int dir) {
  if (dir==(a[i]>a[j])) 
    exchange(i,j);
}


void impBitonicSortParallel(int paddedN) {

  int i,j,k;
  
  for (k=2; k<=paddedN; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
											dummyMethod1();
      #pragma omp parallel for num_threads(4)
      for (i=0; i<paddedN; i++) {
	int ij=i^j;
	if ((ij)>i) {
	  if ((i&k)==0 && a[i] > a[ij]) 
	      exchange(i,ij);
	  if ((i&k)!=0 && a[i] < a[ij])
	      exchange(i,ij);
	}
      }
											dummyMethod2();
    }
  }
}


void impBitonicSort(int paddedN) {

  int i,j,k;
  
  for (k=2; k<=paddedN; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      for (i=0; i<paddedN; i++) {
  int ij=i^j;
  if ((ij)>i) {
    if ((i&k)==0 && a[i] > a[ij]) 
        exchange(i,ij);
    if ((i&k)!=0 && a[i] < a[ij])
        exchange(i,ij);
  }
      }
    }
  }
}


int findMax(int* arr, int N){
  int max = arr[0];
  for (int i = 0; i < N; i++){
    if (arr[i] > max){
      max = arr[i]; 
    }
  }
  return max;
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