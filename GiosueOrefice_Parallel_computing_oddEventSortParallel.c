#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void oddEvenSort(int *a,int N);
void swap(int *a,int *b);
void merge(int a[], int p, int q, int r);
void mergeSort(int a[], int p, int r);

int main(int argc, char const *argv[])
{
	int *arr,*arr2;
	int i;


	int N=1000;
	arr = (int *)malloc(N*sizeof(int));
	arr2 = (int *)malloc(N*sizeof(int));
	srand(time(NULL));
dummyMethod3();
	for ( i = 0; i < N; i++){
		arr[i] = 1+ rand()%10000;
		arr2[i] = arr[i];
	}
dummyMethod4();

	omp_set_num_threads(2);
	double t0 = omp_get_wtime();
	oddEvenSort(arr,N);
	double t1 = omp_get_wtime();
	printf("TIME ODD EVEN SORT PARALLEL: %0.6f\n",t1-t0);

	 t0 = omp_get_wtime();
	mergeSort(arr2,0,N-1);
	 t1 = omp_get_wtime();
	printf("TIME MERGE SORT SEQUENTIAL: %0.6f\n",t1-t0);

	//PRINT 

	/*for ( i = 0; i < N; i++)
		printf("%d  ",arr[i]); */

	/*
	printf("\n");
	for ( i = 0; i < N; i++)
		printf("%d  ",arr2[i]);
	*/
	
	return 0;
}

void oddEvenSort(int *a,int N){
	 int sw1 = 1, start = 0, i;

    while(sw1 || start){

      sw1 = 0;
															dummyMethod1();
      #pragma omp parallel for private(i)
        for(i = start; i < N - 1; i += 2) 
        {
          if(a[i] > a[i+1])
          {
            swap(&a[i],&a[i+1]);
            sw1 = 1;
          }
        }
															dummyMethod2();

        start = !start;

     }
}

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;

}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
							dummyMethod3();
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
							dummyMethod4();
							dummyMethod3();
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
							dummyMethod4();
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
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