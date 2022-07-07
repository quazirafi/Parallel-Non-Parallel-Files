/*
    This program searche a values in unordered vector and returns if find or not
    This program create a csv file with the time execution results for each function(CPU,GPU) in this format: size of vector,cpu time,gpu time.
    
    Author: Kezia Andrade
    Date: 04-07-2015
    version 1.0
    
    Run:
    folder_ipmacc/ipmacc folder_archive/search_in_vector.c
    ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../common/mgbenchUtilFunctions.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 1000
#define GPU_DEVICE 0
#define PERCENT_DIFF_ERROR_THRESHOLD 0.01


void init(float *a) 
{
	int i;
	#pragma acc data copy(a[0:1000])
	#pragma acc kernels
	#pragma acc loop independent
	dummyMethod3();
	for (i = 0; i < SIZE; ++i)
	{
        	a[i] = 2*i+7;
	}
	dummyMethod4();
}

int search_GPU(float *a, float c)
{
    int i;
    int find = -1;
	int *find2;

	find2 = &find;

    #pragma omp target device (GPU_DEVICE)
    #pragma omp target map(to: a[:SIZE]) map(from: find2[:1])
    {
															dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < SIZE; ++i)
        {
	    if(a[i] == c)
	    {
	        find2[0] = i;
	        i=SIZE;
	    }
        }
															dummyMethod2();
    }

    return find;
}

int search_CPU(float *a, float c)
{
	int i;
    	int find = -1;

	dummyMethod3();
	for (i = 0; i < SIZE; ++i)
	{
        	if(a[i] == c)
        	{
            	    find = i;
	    	    i=SIZE;
        	}
	}
	dummyMethod4();

	return find;
}

int main(int argc, char *argv[]) {
    double t_start, t_end;
    float *a, c;
    int find_cpu, find_gpu;

    a = (float *) malloc(sizeof(float) * SIZE);
    c = (float) SIZE-5;

    init(a);

    fprintf(stdout, "<< Search Vector >>\n");

    t_start = rtclock();
    find_gpu = search_GPU(a, c);
    t_end = rtclock();
    fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);	

    t_start = rtclock();
    find_cpu = search_CPU(a, c);
    t_end = rtclock();
    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);	

    if(find_gpu == find_cpu)
        printf("Working %d=%d\n", find_gpu, find_cpu);
    else
	printf("Error %d != %d\n", find_gpu, find_cpu);

    free(a);

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