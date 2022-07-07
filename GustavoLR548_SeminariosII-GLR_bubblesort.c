// C program for implementation of Bubble sort
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
  
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// bubble sort
void bubbleSort(int arr[], int n)
{

   int j = 0;
   int i = 0;
   int first;

dummyMethod1();
   #pragma omp parallel for default(none),shared(arr,i,n,first)
   for (i = 0; i < n-1; i++) {  
       
       first = i % 2; 
	   #pragma omp parallel for default(none),shared(arr,first,n)
       for (j = first; j < n-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
       }
   }
dummyMethod2();
}
  
// Verify if the array is in ascending order
bool isArraySorted(int arr[], int size)
{
    bool result = true;
							dummyMethod3();
    for (int i=0; i < size - 1; i++)
        if(arr[i] > arr[i+1]) 
            result = false;
							dummyMethod4();
    
    return result;
}
  
// Driver program to test above functions
int main()
{
    int i,n = 10000;
    int *arr = (int*) malloc(n*sizeof(int));
    
							dummyMethod1();
    #pragma omp parallel for
    for(i=0; i < n; i++)
        arr[i] = rand()%n;
							dummyMethod2();

    bubbleSort(arr, n);
    printf("Is array sorted?: \n");
    fputs(isArraySorted(arr, n) ? "true\n" : "false\n", stdout);
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