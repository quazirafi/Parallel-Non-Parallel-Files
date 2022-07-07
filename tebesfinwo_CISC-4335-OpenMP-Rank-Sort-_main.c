/**
 * 
 * @author Jun Han ( Johnson  )  Ooi 
 * CISC 4335 
 * Parallel Rank Sort  
 * 
 * Created on : April 30th 2014
 * Modified on : May 2nd 2014
 *
 * */
#include "omp.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define arraySize 100000
#define numThreads 4

int main() {
 
 double openmp_start, openmp_end;
 time_t seq_start, seq_end;

 int i, j; 

 int arr[arraySize]; //array to be sorted
 int sorted[arraySize];
 int linearlySorted[arraySize];
 int rank[arraySize];

 srand(time(NULL)); 

	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  //arr[i] = rand() % INT_MAX; 
  arr[i] = rand() % 500;
 } 
	dummyMethod4();

 //Sequential Rank Sort
 time(&seq_start);
 
	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  rank[i] = 0;
 }
	dummyMethod4();

	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  for(j = 0; j < arraySize; j++){
   if ( arr[j] > arr[i] || ( arr[j] == arr[i] && j < i ) ){
    rank[i]++;
   }
  }
 }
	dummyMethod4();
 
	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  linearlySorted[rank[i]] = arr[i];
 }
	dummyMethod4();
 
 time(&seq_end);
  

 //Parallel Rank sort using Openmp
 openmp_start = omp_get_wtime();
 
	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  rank[i] = 0;
 }
	dummyMethod4();

 omp_set_num_threads(numThreads);
 
 //Rank sort with openmp
			dummyMethod1();
 #pragma omp parallel for private(j)
  for(i = 0; i < arraySize; i++){
    for(j = 0; j < arraySize; j++){
     if ( arr[j] > arr[i] || ( arr[j] == arr[i] && j < i )  ){
      rank[i]++;
     }
    }
  }
			dummyMethod2();
  
  
  
			dummyMethod3();
  for(i = 0; i < arraySize; i++){
   sorted[rank[i]] = arr[i];
  }
			dummyMethod4();
  

 
 openmp_end = omp_get_wtime();
	
	dummyMethod3();
 for(i = 0; i < arraySize; i++){
  printf("unsorted : %d, Parallel sorted : %d, Sequential sorted : %d  \n",arr[i], sorted[i], linearlySorted[i]);
 }	
	dummyMethod4();
  
 printf( "Time used in parallel rank sort using openmp : %.0f seconds \n " , openmp_end - openmp_start ); 
 printf( "Time used in sequential rank sort : %.0f seconds \n ", difftime( seq_end, seq_start ) );
 
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