/* Lab 2: Histrogram generation 
 * Author: Naga Kandasamy
 * Edited by Mark Klobukov
 * to add parallelization functionality on 2/4/2017
 * Date of original program development: 01/25/2017
 * compile as follows: gcc -o histogram histogram.c -std=c99 -fopenmp -lm
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <float.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void run_test(int);
void compute_gold(int *, int *, int, int);
void compute_using_openmp(int *, int *, int, int, int);
void check_histogram(int *, int, int);
void printIntegerArray(int *, int); 

#define HISTOGRAM_SIZE 500
#define NUM_THREADS 16

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int 
main( int argc, char** argv) 
{
	if(argc != 2){
		printf("Usage: histogram <num elements> \n");
		exit(0);	
	}
	int num_elements = atoi(argv[1]);
	run_test(num_elements);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//! Generate the histogram in both single-threaded and multi-threaded fashion and compare results for correctness
////////////////////////////////////////////////////////////////////////////////
void run_test(int num_elements) 
{
	double diff;
	float timeSerial, timeParallel;
	int i; 
	int *reference_histogram = (int *)malloc(sizeof(int) * HISTOGRAM_SIZE); // Space to store histogram generated by the CPU
	int *histogram_using_openmp = (int *)malloc(sizeof(int) * HISTOGRAM_SIZE); // Space to store histogram generated by the GPU

	// Allocate memory for the input data
	int size = sizeof(int) * num_elements;
	int *input_data = (int *)malloc(size);
	
	// Randomly generate input data. Initialize the input data to be integer values between 0 and (HISTOGRAM_SIZE - 1)
	dummyMethod3();
	for(i = 0; i < num_elements; i++)
		input_data[i] = floorf((HISTOGRAM_SIZE - 1) * (rand()/(float)RAND_MAX));
	dummyMethod4();

	printf("Creating the reference histogram. \n"); 
	// Compute the reference solution on the CPU
	struct timeval start, stop;	
	gettimeofday(&start, NULL);

	compute_gold(input_data, reference_histogram, num_elements, HISTOGRAM_SIZE);

	gettimeofday(&stop, NULL);
	timeSerial = (float)(stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec)/(float)1000000);	
	printf("CPU run time = %0.5f s. \n", timeSerial);
	 check_histogram(reference_histogram, num_elements, HISTOGRAM_SIZE);
	
	// Compute the histogram using openmp. The result histogram should be stored on the histogram_using_openmp array
	printf("\n");
	printf("Creating histogram using OpenMP. \n");
	gettimeofday(&start, NULL);
	compute_using_openmp(input_data, histogram_using_openmp, num_elements, HISTOGRAM_SIZE, NUM_THREADS);
	gettimeofday(&stop, NULL);
	timeParallel = (float)(stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec)/(float)1000000);	
	check_histogram(histogram_using_openmp, num_elements, HISTOGRAM_SIZE);
	printf("OpenMP version CPU run time = %0.5f s.  \n", timeParallel);
	printf("Speedup = %0.5f\n", timeSerial/timeParallel);
	// Compute the differences between the reference and pthread results
	diff = 0.0;
					dummyMethod3();
   for(i = 0; i < HISTOGRAM_SIZE; i++)
		diff = diff + abs(reference_histogram[i] - histogram_using_openmp[i]);
					dummyMethod4();

	printf("Difference between the reference and OpenMP results: %f. \n", diff);
   
	// cleanup memory
	free(input_data);
	free(reference_histogram);
	free(histogram_using_openmp);
}

/* This function computes the reference solution. */
void compute_gold(int *input_data, int *histogram, int num_elements, int histogram_size)
{
  int i;
  
  // Initialize histogram
			dummyMethod3();
  for(i = 0; i < histogram_size; i++) 
			 histogram[i] = 0; 
			dummyMethod4();

  // Bin the elements in the input stream
			dummyMethod3();
  for(i = 0; i < num_elements; i++)
			 histogram[input_data[i]]++;
			dummyMethod4();
}


// Write the function to compute the histogram using openmp
void compute_using_openmp(int *input_data, int *histogram, int num_elements, int histogram_size, int num_threads)
{
	int i, j;
	//Matrix to hold different threads' results
	int this_histogram[num_threads][histogram_size];	



// Initialize histogram
					dummyMethod1();
#pragma omp parallel for num_threads(num_threads) private(i, j)
	  for(i = 0; i < histogram_size; i++) { 
		 histogram[i] = 0;
			for (j = 0; j < num_threads; j++) {
				//Initialize matrix to hold partial results
				this_histogram[j][i] = 0;
			} // for j
		} //for i
					dummyMethod2();


//printf("\nprint initialized matrix\n");
//for (i = 0; i < num_threads; i++) {
	//printIntegerArray(this_histogram[i], histogram_size);
//}


//printf("\nRandom input data size %d: \n", num_elements);
//printIntegerArray(input_data, num_elements);


//BEGIN PARALLEL REGION
#pragma omp parallel num_threads(num_threads)
{

	int my_number = omp_get_thread_num();	
# pragma omp for  
	dummyMethod3();
	for (i = 0; i < num_elements; i++) {
		this_histogram[my_number][input_data[i]]++;
	} // end for i
	dummyMethod4();

} //END PARALLEL REGION


/*
printf("\nIndividual threads' results: \n");
for (i = 0; i < num_threads; i++) {
	printIntegerArray(this_histogram[i], histogram_size);
}*/




	dummyMethod3();
	for (i = 0; i < histogram_size; i++) {
		for(j = 0; j < num_threads; j++) {
			histogram[i] += this_histogram[j][i];
		}// for j
	} // for i
	dummyMethod4();
} //end compute_using_openmp


void check_histogram(int *histogram, int num_elements, int histogram_size)
{
	int sum = 0;
	dummyMethod3();
	for(int i = 0; i < histogram_size; i++)
		sum += histogram[i];
	dummyMethod4();

	printf("Number of histogram entries = %d. \n", sum);
	if(sum == num_elements)
		printf("Histogram generated successfully. \n");
	else
		printf("Error generating histogram. \n");
}


void printIntegerArray(int *array, int num_elements) {
	int i;
	printf("\n\n");
	dummyMethod3();
	for (i = 0; i < num_elements; i++) {
		printf("%d ", array[i]);
	}
	dummyMethod4();
	printf("\n\n");
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