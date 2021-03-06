#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct timeval st, et;
void swap(int*, int, int);
void rng(int*, int, int*);
void buildDummy(int*, int, int, int);
void impBitonicSortPar(int*, int, int);
void impBitonicSortSer(int*, int);
int getPowTwo(int);
void writeToFile(int*, int, char*);

int thr;
int main(int argc, char **argv) {
  int n, dummy_n, threads, test, max_x;
  int* arr;
  int* arr2;
  thr = omp_get_max_threads();
  // get maximum effective threads
  threads = omp_get_max_threads();

  if (argc < 2) {
    printf("Usage: %s <n> <p>\nwhere <n> is problem size, <p> is number of thread (optional)\n\n", argv[0]);
    exit(1);
  }

  if (argc == 3){
    // use for custom threads number
    threads = atoi(argv[2]);
  }
  // true for test with 1,2,4,8,...,256 threads number
  test = threads<=0;
  if(test){
    printf("test\n");
  }

  // get problem size;
  n = atoi(argv[1]);
  // get dummy_n from nearest power of two
  dummy_n = getPowTwo(n);

  // prepare random numbers
  arr = (int*) malloc(dummy_n*sizeof(int));
  if(!arr){
    printf("Unable to allocate memory\n");
    exit(1);
  }
  rng(arr,n,&max_x);
  buildDummy(arr,n,dummy_n,max_x);

  // copy
  arr2 = (int*) malloc(dummy_n*sizeof(int));
  memcpy(arr2,arr,dummy_n*sizeof(int));

  // write random numbers to input file
  writeToFile(arr,n,"./data/input");

  // execute serial
  gettimeofday(&st,NULL);
  impBitonicSortSer(arr,dummy_n);
  gettimeofday(&et,NULL);
  int elapsed_serial = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Execution serial time: %d micro sec\n",elapsed_serial);

  // execute paralel
  gettimeofday(&st,NULL);
  impBitonicSortPar(arr2,dummy_n,threads);
  gettimeofday(&et,NULL);
  int elapsed_paralel = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Execution paralel time: %d micro sec\n",elapsed_paralel);

  // calculate speedup
  printf("Speedup : %.3f\n",(float)elapsed_serial/elapsed_paralel);

  writeToFile(arr,n,"./data/output");
  free(arr);
  free(arr2);
  return 0;
}

void writeToFile(int* arr, int n, char* path){
  FILE* f = fopen(path,"w");
			dummyMethod3();
  for(int i=0; i<n; i++) {
      fprintf(f, "%d\n", arr[i]);
  }
			dummyMethod4();
  fclose(f);
}

void rng(int* arr, int n, int* max_x) {
  int seed = 13515097;
  srand(seed);
			dummyMethod3();
  for(long i = 0; i < n; i++) {
    arr[i] = (int)rand();
    *max_x = ((i==0 || *max_x<arr[i])?arr[i]:*max_x);
  }
			dummyMethod4();
}

void buildDummy(int* arr,int N,int dummy_n, int max_x){
			dummyMethod3();
  for(long i = N; i < dummy_n; i++) {
    arr[i]=max_x;
  }
			dummyMethod4();
}

void swap(int* a, int i, int j) {
  int t;
  t = a[i];
  a[i] = a[j];
  a[j] = t;
}

/*
Imperative paralel bitonic sort
*/
void impBitonicSortPar(int* a, int n, int threads) {
  int i,j,k;
  int dummy_n = getPowTwo(n);

  for (k=2; k<=dummy_n; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      // bitonic increasing
											dummyMethod1();
      #pragma omp parallel for num_threads(threads) private(i) shared(n,j,k)
      for (i=0; i<n; i++) {
        int ij=i^j;
        if ((ij)>i) {
          // monotonic increasing
          if ((i&k)==0 && a[i] > a[ij]) swap(a,i,ij);
          // monotonic decreasing
          if ((i&k)!=0 && a[i] < a[ij]) swap(a,i,ij);
        }
      }
											dummyMethod2();
    }
  }
}

/*
Imperative serial bitonic sort
*/
void impBitonicSortSer(int* a, int n) {
  int i,j,k;
  int dummy_n = getPowTwo(n);

  for (k=2; k<=dummy_n; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      // bitonic increasing
      for (i=0; i<n; i++) {
        int ij=i^j;
        if ((ij)>i) {
          // monotonic increasing
          if ((i&k)==0 && a[i] > a[ij]) swap(a,i,ij);
          // monotonic decreasing
          if ((i&k)!=0 && a[i] < a[ij]) swap(a,i,ij);
        }
      }
    }
  }
}


int getPowTwo(int n){
  int d=1;
  while (d>0 && d<n) d<<=1;
  return d;
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