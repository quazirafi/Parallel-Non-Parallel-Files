//OpenMP version.  Edit and submit only this file.
/* Enter your details below
* Name: 
* UCLA ID: 
* Email: 
*/

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "utils.h"

void work_it_par(long *old, long *new) 
{


	int i, j, k;
	int u, v, w;
	int z;

	int arr[27];

	long compute_it;
	long aggregate = 1.0;

	int need = we_need_the_func();
	int gimmie = gimmie_the_func();
	

	long accumulator;
	int iIndex;
	int jIndex;
	int index;
	int dim2 = DIM*DIM;

	//lookup table
	int counter = 0;
	int val;
	dummyMethod3();
	for (u = -1; u <= 1; u++)
	{
		for (v = -1; v <= 1; v++)
		{
			for (w = -1; w <= 1; w++)
			{
				val = u * dim2 + v * DIM + w;
				arr[counter] = val;
				counter++;
			}
		}
	}
	dummyMethod4();


	//all values that should be placed in histogrammy
	long a0 = 0;
	long a1 = 0;
	long a2 = 0;
	long a3 = 0;
	long a4 = 0;
	long a5 = 0;
	long a6 = 0;
	long a7 = 0;
	long a8 = 0;
	long a9 = 0;


	
	dummyMethod1();
#pragma omp parallel for private(j, k, z, accumulator, jIndex, index, iIndex, compute_it) reduction(+: aggregate, a0,a1,a2,a3,a4,a5,a6,a7,a8,a9)
	for (i = 1; i < DIM - 1; i++)
	{
		iIndex = i * dim2;
		jIndex = 0;
		for (j = 1; j < DIM - 1; j++)
		{
			jIndex += DIM;
			for (k = 1; k < DIM - 1; k++)
			{
				//calculate the current position in this 3d box
				index = iIndex + jIndex + k;

				//increase aggregate first
				compute_it = old[index] * need;
				aggregate += compute_it / gimmie;


				//calculate the average of the arounding 3*3*3 little block, and update new at the end of the loop
				accumulator = 0;
				long subsum1 = 0;
				long subsum2 = 0;
				long subsum3 = 0;
				//loop unrolling
				for (z = 0; z < 27; z+=3)
				{
					subsum1 += old[index + arr[z]];
					subsum2 += old[index + arr[z + 1]];
					subsum3 += old[index + arr[z + 2]];
				}

				accumulator += (subsum1 + subsum2 + subsum3);
					

				long value = accumulator / 27;

				
		
				//calculate parameter
				int par = value / 100;
				
				//replace the branch with direct calculation
				a0 += (unsigned)par >> 31;
				a0 += !(par ^ 0);
				a1 += !(par ^ 1);
				a2 += !(par ^ 2);
				a3 += !(par ^ 3);
				a4 += !(par ^ 4);
				a5 += !(par ^ 5);
				a6 += !(par ^ 6);
				a7 += !(par ^ 7);
				a8 += !(par ^ 8);

				//use int64_t type to avoid potential overflow
				int64_t tmp = (int64_t)(par) - 9;
				a9 += ((tmp >> 63) + 1);


				//update new
				new[index] = value;

			}
		}
	}
	dummyMethod2();



	printf("AGGR:%ld\n", aggregate);


	

	
	//update histogrammy
	histogrammy[0] = a0;
	histogrammy[1] = a1;
	histogrammy[2] = a2;
	histogrammy[3] = a3;
	histogrammy[4] = a4;
	histogrammy[5] = a5;
	histogrammy[6] = a6;
	histogrammy[7] = a7;
	histogrammy[8] = a8;
	histogrammy[9] = a9;
	

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