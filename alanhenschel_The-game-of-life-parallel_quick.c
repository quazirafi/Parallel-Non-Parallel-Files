#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void printArray(int arr[], int size) 
{ 
    int i; 
dummyMethod3();
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
dummyMethod4();
} 
// A utility function to swap two elements 
void swap(int* a, int* b) 
{   
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
							dummyMethod1();
    #pragma omp parallel for
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
							dummyMethod2();
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        
        int pi = partition(arr, low, high); 
        
        // Separately sort elements before 
        // partition and after partition 
        #pragma omp task shared(arr) firstprivate(low,pi) if(50)
        {
            //int ID2 = omp_get_thread_num();
            //printf("\nTHREAD ATUAL2222:%d\n",ID2);

            quickSort(arr, low, pi - 1);
            //printArray(arr,pi-1);
        }
        #pragma omp task shared(arr) firstprivate(high,pi) if(50)
        {
            int ID = omp_get_thread_num();
            printf("\nTHREAD ATUAL:%d\n",ID);
            quickSort(arr, pi + 1, high);
            //int ID = omp_get_thread_num();
            //printf("\nTHREAD ATUAL:%d\n",ID);
            //printf("\nMEIOOOOOOO\n");
            //printArray(arr,high);
        }
        #pragma omp taskwait
    } 
} 
  
/* Function to print an array */
  
// Driver program to test above functions 
void main() 
{ 
    int arr[] = {0, 2, 7, 4, 8, 6, 5, 1, 3, 9,10,11,12,13,14,15,16,7,55,90}; 
    //int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    omp_set_num_threads(5);
    #pragma omp parallel default(none) shared(arr,n)
    {
    #pragma omp single
    {
    int ID2 = omp_get_thread_num();
    printf("\nTHREAD gerenciador:%d\n",ID2);
    quickSort(arr, 0, n-1);
    }
    }
    printf("Sorted array: "); 
    printArray(arr, n); 
     
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