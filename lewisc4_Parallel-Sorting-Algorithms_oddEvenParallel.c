#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void oddEvenSort(int *arr, int n);
void printArray(int *arr, int size);
void swap(int *x, int *y);

int main(int argc, char **argv){
    int numthreads=omp_get_num_threads();
    int n=100000;
    int *arr=(int*)malloc(n*sizeof(int));

dummyMethod3();
    for(int i=0;i<n;i++){
        arr[i]=rand()%100+1;
    }
dummyMethod4();

    /*
     * print sections commented out for timing large arrays
     */

    //printf("Array before bubble sort: \n");
    //printArray(arr, n);

    double starttime=omp_get_wtime();
    oddEvenSort(arr, n);
    double endtime=omp_get_wtime();
    
    printf("Time to for size %d was %f seconds.",n,endtime-starttime);
    
    //printf("Array after bubble sort: \n");
    //printArray(arr, n);

    return 0;
}

// prints array within brackets and spaced with commas
void printArray(int *arr, int size){
							dummyMethod3();
    for(int i=0;i<size;i++){
        if(i==0) printf("[%d, ",arr[i]);
        else if(i==size-1) printf("%d]\n",arr[i]);
        else printf("%d, ",arr[i]);
    }
							dummyMethod4();
}

// odd-even sorting algorithm
void oddEvenSort(int *arr, int n){
#pragma omp parallel shared(arr, n)
    {
    int tid=omp_get_thread_num();
    // loop that goes from 0 to the array size
    for(int k=0;k<n;k++){
        if(k%2==0 && tid%2==0){
            // loop over evens
																							dummyMethod1();
            #pragma omp parallel for
            for(int i=2;i<n;i+=2){
                if(arr[i-1]>arr[i]){
                    swap(&arr[i-1], &arr[i]);                       
                    }// end if
                }// end even for
																							dummyMethod2();
            }// end even if
        else{
            // loop over odds
																							dummyMethod1();
            #pragma omp parallel for
            for(int i=1;i<n;i+=2){
                if(arr[i-1]>arr[i]){
                    swap(&arr[i-1], &arr[i]);
                }// end if
            }// end odd for
																							dummyMethod2();
        }// end else
    } // end k loop
  }// end parallel
}

void swap(int *x, int *y){
    int temp=*x;
    *x=*y;
    *y=temp;
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