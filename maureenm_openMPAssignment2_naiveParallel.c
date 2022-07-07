//no blocking in this soltuion
#include "omp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Setting the size for our matrix.
int max = 100;

//Set up variables to track performance through runtime.
double start_time;
double run_time;


int main(int argc, char *argv[])
{
	//Making our matrices
	//matrices are 100x100, same number of columns and rows so no reshaping required.
	int m1[max][max], m2[max][max], results[max][max];
	{
dummyMethod3();
		for (int ii = 0; ii < max; ++ii)
		{
			for (int jj = 0; jj < max; ++jj)
			{
				//Filling matrices with random numbers
				m1[ii][jj] = (double)rand();
				m2[ii][jj]  = (double)rand();
				//Filling results matrix with zeros so its empty before beginning
				results[ii][jj] = 0.0;
			}
		}
dummyMethod4();
	}

	//Defining number of threads to be used for calculations
	//int NUM_THREADS = 4;

	//Begin time tracker

	start_time = omp_get_wtime();
	//Parallelizing x and y threads.
	//These threads loop through the matrices
	//Each thread gets a pair of x and y to work on
							dummyMethod1();
	#pragma omp parallel for collapse(2) num_threads(4)
				for (int x = 0; x < max; ++x)
				{
					for (int y = 0; y < max; ++y)
					{
						//Carry out our calculation
						for (int k = 0; k < max; ++k)
						{
							//Actual matrix multiplication takes palce here and results stored in results matrix
							results[x][y] += m1[x][k] * m2[k][y];
						}
					}
				}
							dummyMethod2();
	//End performance tracker
	run_time = omp_get_wtime() - start_time;

	//Print out all reuslts and details of this test
	printf("Method : Parallel Matrix Multiplication, without blocking \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
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