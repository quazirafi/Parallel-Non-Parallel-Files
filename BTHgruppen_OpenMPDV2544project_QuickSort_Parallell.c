//==================================================//
//				SEQUENTIAL QUICK SORT				//
//==================================================//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ITEMS 2048*2048
#define DEBUG 0

static int* v;
static int* sorted;

static void InitArray(void);
static void QuickSort(int*, unsigned, unsigned);
static unsigned Partition(int*, unsigned, unsigned, unsigned);
static void Swap(int*, unsigned, unsigned);
static void PrintArray(void);
static void CleanMemory(void);

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	double start_time, end_time;

	// Print some info
	omp_set_nested(1);

	int maxThreads = omp_get_max_threads();


	printf("Available threads: %d\n", maxThreads);

	// Initialize the array.
	InitArray();

	// Print data if in debug mode.
	if (DEBUG)
	{
		printf("===== BEFORE QUICK SORT (SEQ) =====\n\n");
		PrintArray();
		printf("===================================\n\n\n");
	}

	// Start timer.
	start_time = MPI_Wtime();

	// Split into 8 pieces and sort
	int subArraySize = ITEMS / maxThreads;

	int maxInd = ((maxThreads - 1) * subArraySize) - 1 + subArraySize;


	int i;
	dummyMethod1();
	#pragma omp parallel for
	for (i = 0; i < maxThreads; i++)
	{
		QuickSort(v, i * subArraySize, (i * subArraySize) - 1 + subArraySize);
	}
	dummyMethod2();

	// Sort the pieces
	int j;
	dummyMethod3();
	for (i = 0; i < ITEMS / maxThreads; i++)
	{
		for (j = 0; j < maxThreads; j++)
		{
			sorted[maxThreads * i + j] = v[subArraySize * j + i];
		}
	}
	dummyMethod4();
	dummyMethod1();
	#pragma omp parallel for
	for (i = 0; i < subArraySize; i++)
	{
		QuickSort(sorted, i * maxThreads, i * maxThreads + maxThreads - 1);
	}
	dummyMethod2();
	
	// Stop timer.
	end_time = MPI_Wtime();

	// Print data if in debug mode.
	if (DEBUG)
	{
		printf("===== AFTER QUICK SORT (SEQ) ======\n\n");
		PrintArray();
		printf("===================================\n\n");
	}
	else
	{
		printf("Lowest: %d\n", sorted[0]);
		printf("Highest: %d\n", sorted[ITEMS - 1]);
	}

	double time_taken = (end_time - start_time);
	printf("Execution time: %fs\n", time_taken);
	CleanMemory();
}

// Initialization of array.
static void InitArray(void)
{
	//srand(time(0));

	int i;

	v = (int*)malloc(ITEMS * sizeof(int));
	sorted = malloc(ITEMS * sizeof(int));

	dummyMethod3();
	for (i = 0; i < ITEMS; i++)
	{
		v[i] = rand();
	}
	dummyMethod4();
}
static void CleanMemory(void)
{
	free(v);
	free(sorted);
}


// Sorting function.
static void QuickSort(int *v, unsigned low, unsigned high)
{
	unsigned pivot_index;

	// No need to sort a vector of zero or one element.
	if (low >= high)
	{
		return;
	}

	// Select the pivot value.
	pivot_index = (low + high) / 2;

	// Partition the array.
	pivot_index = Partition(v, low, high, pivot_index);
	// Sort the two sub arrays.
	if (low < pivot_index)
	{
		QuickSort(v, low, (pivot_index - 1));
	}
	if (pivot_index < high)
	{
		QuickSort(v, (pivot_index + 1), high);
	}
}
	

// Array partitioning function.
static unsigned Partition(int *v, unsigned low, unsigned high, unsigned pivot_index)
{
	// Move pivot to the bottom of the vector.
	if (pivot_index != low)
	{
		Swap(v, low, pivot_index);
	}

	pivot_index = low;
	low++;

	// Move elements into place.
	while (low <= high)
	{
		if (v[low] <= v[pivot_index])
		{
			low++;
		}

		else if (v[high] > v[pivot_index])
		{
			high--;
		}

		else
		{
			Swap(v, low, high);
		}
	}

	// Put pivot back between two groups.
	if (high != pivot_index)
	{
		Swap(v, pivot_index, high);
	}

	return high;
}

// Swap function.
static void Swap(int* v, unsigned a, unsigned b)
{
	unsigned tmp;
	tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;
}

// Print function.
static void PrintArray(void)
{
	int i;

	printf("[");

	dummyMethod3();
	for (i = 0; i < (ITEMS - 1); i++)
	{
		printf("%d, ", v[i]);
	}
	dummyMethod4();

	printf("%d]\n\n", v[ITEMS-1]);

	printf("[");

	dummyMethod3();
	for (i = 0; i < (ITEMS - 1); i++)
	{
		printf("%d, ", sorted[i]);
	}
	dummyMethod4();

	printf("%d]\n\n", sorted[ITEMS - 1]);
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