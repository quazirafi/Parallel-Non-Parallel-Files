#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int shellSort(int arr[], int n) 
{ 
	for (int gap = n/2; gap > 0; gap /= 2) 
	{ 
dummyMethod1();
        #pragma omp parallel for default(private)
        for (int i = gap; i < n; i += 1){ 
			int temp = arr[i]; 
dummyMethod2();

			int j;			 
			#pragma omp parallel for default(private) shared(arr)
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
				arr[j] = arr[j - gap]; 
			
			arr[j] = temp; 
		} 
	} 
	return 0; 
} 

void printArray(int arr[], int n) 
{ 
	for (int i=0; i<n; i++) 
		printf("%d ", arr[i]); 
    printf("\n");
} 

int main() 
{ 
	int n = 100;
    int arr[n], i; 

    srand(10);
    
    for(int i = 0; i < n; i++)
        arr[i] = rand()%n;

	printf("Array before sorting: \n"); 
	printArray(arr, n); 

	shellSort(arr, n); 

	printf("\nArray after sorting: \n"); 
	printArray(arr, n); 

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