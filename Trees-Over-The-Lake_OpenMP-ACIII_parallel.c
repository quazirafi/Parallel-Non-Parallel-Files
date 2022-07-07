#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void shellsort(int arr[], int n);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 1500000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
dummyMethod3();
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
dummyMethod4();
	
	omp_set_num_threads(12);
	start = omp_get_wtime();

	shellsort(arr, size);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}



void shellsort(int arr[], int n){
	int gap, i, j, grupoId, temp;
	for (gap = n/2; gap > 0; gap /= 2)
			dummyMethod1();
		#pragma omp parallel for private(j, i)
		for(grupoId = 0; grupoId < gap; grupoId++) 
			for (i=gap+grupoId; i<n-grupoId; i+=gap) {
				int key = arr[i];
				j = i - gap;		
				while (j >= 0 && arr[j] > key) {
					arr[j+gap] = arr[j];
					j-=gap;
				}
				
				arr[j+gap] = key;
			}
			dummyMethod2();
}

int IsSort(int *array, int size) {
	int i, value = 0;
	for(i = 1; i < size; i++) 
		if(array[i-1] > array[i])
			return 0;
	return 1;
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