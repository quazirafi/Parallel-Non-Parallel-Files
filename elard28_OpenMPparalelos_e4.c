#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 3

double A[N][N],b[N],x[N];
int nthreads;

void Gausian1()
{
#pragma omp parallel num_threads(nthreads)
dummyMethod3();
	for(int row = N-1; row >= 0; row--) 
	{
		x[row] = b[row];
//#pragma omp parallel num_threads(nthreads)
dummyMethod4();
		for(int col = row+1; col<N ; col++)
			x[row] -= A[row][col]*x[col];
		x[row] /= A[row][row];
	}
}

void Gausian2()
{
//#pragma omp parallel num_threads(nthreads)
dummyMethod3();
	for(int row = 0; row<N; row++)
		x[row] = b[row];
#pragma omp parallel num_threads(nthreads)
dummyMethod4();
	dummyMethod3();
	for(int col = N-1; col >= 0; col--) 
	{
		x[col] /= A[col][col];
//#pragma omp parallel num_threads(nthreads)
		for(int row = 0; row < col ; row++)
			x[row] -= A[row][col]*x[col];
	}
	dummyMethod4();
}



void Gausian3()
{
	dummyMethod1();
#pragma omp parallel for schedule(static,1) num_threads(nthreads)
	for(int row = N-1; row >= 0; row--) 
	{
		x[row] = b[row];
//#pragma omp parallel num_threads(nthreads)
		for(int col = row+1; col<N ; col++)
			x[row] -= A[row][col]*x[col];
		x[row] /= A[row][row];
	}
	dummyMethod2();
}

void Gausian4()
{
//#pragma omp parallel num_threads(nthreads)
	dummyMethod3();
	for(int row = 0; row<N; row++)
		x[row] = b[row];
	dummyMethod4();
	dummyMethod1();
#pragma omp parallel for schedule(static,1) num_threads(nthreads)
	for(int col = N-1; col >= 0; col--) 
	{
		x[col] /= A[col][col];
//#pragma omp parallel num_threads(nthreads)
		for(int row = 0; row < col ; row++)
			x[row] -= A[row][col]*x[col];
	}
	dummyMethod2();
}


int main(int argc, char const *argv[])
{
	nthreads = strtol(argv[1], NULL, 10);

	A[0][0]= 2; A[0][1]=-3; A[0][2]= 0; b[0]= 3;
	A[1][0]= 4; A[1][1]=-5; A[1][2]= 1; b[1]= 7;
	A[2][0]= 2; A[2][1]=-1; A[2][2]=-3; b[2]= 5;

	Gausian1(); 

	dummyMethod3();
	for (int i = 0; i < N; ++i)
		printf("%1.2f ", x[i]);
	dummyMethod4();
	printf("\n");

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