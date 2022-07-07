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
//Initializing variables used in for loops.
int i, j, x, y, k;

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
	//Setting a fixed block size which will be 10x10 squares
	int block  = 10;

	//Begin time tracker
	start_time = omp_get_wtime();

	//Create out blocks, stepping up in blocks
	dummyMethod1();
#pragma omp parallel for collapse(2) num_threads(4)  private( y, x, k)
	for (int i = 0; i < max; i += block)
	{
		//counting down in blocks
		for (int j = 0; j < max; j += block)
		{
			//Parallelizing x and y threads.
			//These threads loop through the elements in our blocks
			//Each thread gets a pair of x and y to work on
			//Move along the rows of the block.
			for (int y = 0; y < block; ++y)
			{
				//Move along the columns of the block.
				for (int x = 0; x < block; ++x)
				{
					//Defining the critical region
					//#pragma omp critical
					//Reads rows and columns of blocks and carry out our calculation
					for (int k = 0; k < max; ++k)
					{
						//Actual matrix multiplication takes palce here and results stored in results matrix
						results[i + x][j + y] += m1[i + x][k] * m2[k][j + y];
					}
				}
			}
		}
	}
	dummyMethod2();

	//End performance tracker
	run_time = omp_get_wtime() - start_time;
	//Print out all reuslts and details of this test
	printf("Method : Final Design, Blocked Matrix Multiplication \nRuntime : %f\n", run_time );
	printf("Deimensions: %dx%d\n", max, max);
	printf("Block size: %dx%d \nNumber of blocks : %d\nNumber of Threads: ", block, block, block *block);
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