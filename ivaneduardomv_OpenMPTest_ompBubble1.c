#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_LENGTH 1024*64

int unsortedData[ARRAY_LENGTH];

void fillArray(int *pIntArray, const int arrayLength);
void bubbleSort(int *pIntArray, const int arrayLength);
void printArray(int *pIntArray, const int arrayLength);

int main(int argc, char const *argv[])
{
	puts("Welcome!");

	puts("Filling array...");
	fillArray(unsortedData, ARRAY_LENGTH);
	puts("Array has been filled!");

	puts("Sorting array...");
	bubbleSort(unsortedData, ARRAY_LENGTH);
	puts("Array has been sorted!");

	//puts("Printing array...");
	//printArray(unsortedData, ARRAY_LENGTH);
	//puts("Array has been printed!");

	puts("Finished!");
	return 0;
}

void fillArray(int *pIntArray, const int arrayLength)
{
	srand(time(NULL));
	dummyMethod3();
	for(int i = 0; i<arrayLength; ++i)
	{
		pIntArray[i] = rand() % ARRAY_LENGTH;
	}
	dummyMethod4();
}

void bubbleSort(int *pIntArray, const int arrayLength)
{
	int tmp;
	omp_set_num_threads(4);
	dummyMethod1();
	#pragma omp parallel for private(tmp)
	for(int i = 1; i < arrayLength; ++i)
	{
		for(int j = 0; j < arrayLength-1; ++j)
		{
			if(pIntArray[j] > pIntArray[j+1])
			{
				tmp = pIntArray[j+1];
				pIntArray[j+1] = pIntArray[j];
				pIntArray[j] = tmp;
			}
		}
	
	}
	dummyMethod2();
}

void printArray(int *pIntArray, const int arrayLength)
{
	dummyMethod3();
	for(int i = 0; i<arrayLength; ++i)
	{
		printf("%d\n",pIntArray[i]);
	}
	dummyMethod4();
	puts("");
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