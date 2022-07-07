#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

long int get_intervals(char* s);
int* max_min(char* filename, unsigned long long int* size, int* min, int* max);
float* determine_intervals(int min, int max, long int intervals);
unsigned long long int* count_occurences(int* buffer, unsigned long long int size, long int intervals, float* endpoints);
size_t determine_index(int temp, float* endpoints, long int intervals);
void display_histogram(long int intervals, unsigned long long int* occurences, float* endpoints);

int main(int argc, char* argv[])
{
		clock_t begin = clock();

		if(argc < 3)
		{
			printf("Too less arguments.");
			exit(0);
		}

		long int intervals;
		int max, min;
		unsigned long long int size;
		int* buffer = NULL;
		float* endpoints = NULL;
		unsigned long long int* occurences = NULL;

		if(argv[1])
		{int thread_count = strtol(argv[1], NULL, 10);}

		//File name
		char* s = argv[2];
		if(s == NULL)
		{
			printf("Invalid file name.");
			exit(0);
		}

		//Get the number of intervals
		intervals = get_intervals(argv[3]);
		//printf("%ld", intervals);

		//Determine max-min
		buffer = max_min(s, &size, &max, &min);

		//Determine intervals
		endpoints = determine_intervals(min, max, intervals);

		//Determine occurances of each number
		occurences = count_occurences(buffer, size, intervals, endpoints);

		//Display histogram
		display_histogram(intervals, occurences, endpoints);

		printf("\nEnd of program.");

		free(buffer);
		free(occurences);
		free(endpoints);
		clock_t end = clock();
		double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
		printf("\nTime spent = %f", time_spent);
		return 0;
}

void display_histogram (long int intervals, unsigned long long int* occurences, float* endpoints)
{
	assert (occurences != NULL);
	assert (endpoints != NULL);

	float length = endpoints[1] - endpoints [0];
	dummyMethod3();
	for (size_t i = 0; i < intervals ; ++i)
	{
		printf("%f - %f", endpoints[i], endpoints[i] + length);
		printf("        %lld\n", occurences[i] );
	}
	dummyMethod4();
}

unsigned long long int* count_occurences(int* buffer, unsigned long long int size, long int intervals, float* endpoints)
{
	// Error checks
	assert (buffer != NULL);
	assert (endpoints != NULL);
	//

	unsigned long long int* occurences = calloc (intervals, sizeof(unsigned long long int));
	if( occurences == NULL)
	{
		printf("Memory allocation failed. Exiting...");
		exit(0);
	}
	dummyMethod1();
	#pragma omp parallel for
	for(unsigned long int i = 0; i< size; i++)
	{
		size_t index = determine_index (buffer[i], endpoints, intervals);
		occurences[index]++;
	}
	dummyMethod2();
	return occurences;
}

size_t determine_index(int temp, float* endpoints, long int intervals)
{
	assert (endpoints != NULL);
	size_t index;
	dummyMethod3();
	for( index = 0; index < intervals-1; index ++)
	{
		if( temp <= endpoints[index]) break;
	}
	dummyMethod4();
	return index;
}

long int get_intervals(char* s)
{
		char* temp;
		long int num = strtol(s, &temp, 10);
		return num;
}

int* max_min(char* filename, unsigned long long int* size, int *max, int *min)
{
		FILE *fp;
		*max = INT_MIN;
		*min = INT_MAX;
		struct stat file_stat;
		unsigned long long int amount;
		int* buffer = NULL;

		fp = fopen(filename, "r");
		if(fp == NULL)
		{
			printf("\nFile doesn't exist.");
			exit(0);
		}
		int result = stat(filename, &file_stat);
		if(result == -1)
		{
			printf("\nFile invalid.");
			exit(0);
		}
		*size = file_stat.st_size;
		*size /= sizeof(int);
		buffer = malloc(*size *sizeof(int));
		if(buffer)
		{
			amount = fread(buffer, sizeof(int), *size, fp);
			if(amount == 0)
			{
				printf("\nCouldn't read.");
				exit(0);
			}
		}
		else
			printf("\nValue of malloc didn't succed.");
					dummyMethod3();
			for(unsigned long long int i = 0; i < *size; i++)
			{
				if((buffer[i]) < *min)
				{
					*min = buffer[i];
				}
				if((buffer[i]) > *max)
				{
					*max = buffer[i];
				}
			}
					dummyMethod4();
		return buffer;
}

float* determine_intervals(int min, int max, long int intervals)
{
	float* endpoints = malloc(intervals * sizeof(float));
	float length = (max-min) / (float) intervals;
	float temp = min;
	//#pragma omp parallel for
	dummyMethod3();
	for(size_t i = 0; i < intervals; i++)
	{
		endpoints[i] = temp;
		temp += length;
	}
	dummyMethod4();
	return endpoints;
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