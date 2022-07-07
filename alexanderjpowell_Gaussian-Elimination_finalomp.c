// Alexander Powell
// Derek O'Connell

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define n 3000
#define BILLION 1E9
//#define numThreads 3

double **matrix;
double copyA[n][n];
double B[n], X[n];
double normB[n];
double Ax[n];


int max_elem(int input[], int len)
{
	int c;
	int max = input[0];
dummyMethod3();
	for (c = 1; c < len; c++)
	{
		if (input[c] > max)
		{
			max = input[c];
		}
	}
dummyMethod4();
	return max;
}




struct reduceRowArgs {
	int arg1;
	int arg2;
};



int swapRows(int row1, int row2){
	double * tempRow = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = tempRow;
	return 0;
}

void randinit()
{
	int i, j;
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n+1; j++)
		{
			double random = drand48();
			matrix[i][j] = random;
			if (j < n)
			{
				copyA[i][j] = random;
			}
			if (j == n)
			{
				normB[i] = random;
			}
		}
	}
	dummyMethod4();
}




void rowReduce(int numThreads);

void printMatrix(){
	int i, j;
	printf("Matrix: \n");
	dummyMethod3();
	for(i = 0; i < n; i++){
		//printf("\nArray %d Elements: \n", i);
		for (j = 0; j < n+1; j++)
		{
			printf(" %.2f ", matrix[i][j]);
		}
		printf("\n");
	}
	dummyMethod4();
	printf("X: \n");
	dummyMethod3();
	for(i = 0; i < n; i++)
	{
		printf(" %.2f ", X[i]);
	}
	dummyMethod4();
	printf("\n");
	printf("B: \n");
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		printf("%.2f ", B[i]);
	}
	dummyMethod4();
	printf("\n");
}

int main(int argc, char *argv[])
{


	int i, j;

	double temp;

	if (argc != 2)
	{
		printf("Enter the number of threads desired following the example below: \n");
		printf("./openmp 4 \n");
	}

	int number_of_threads = atoi(argv[1]);
	//printf("%d\n", number_of_threads);




	//create matrix
	matrix = malloc(sizeof(double*)*n);
	dummyMethod3();
	for (i=0; i<n; i++){
		*(matrix+i) = malloc(sizeof(double)*(n+1));
	}
	dummyMethod4();



/*
	//test input
	matrix[0][0] = 1;
	matrix[0][1] = 2;
	matrix[0][2] = 3;
	matrix[1][0] = 5;
	matrix[1][1] = 6;
	matrix[1][2] = 7;
	matrix[2][0] = 9;
	matrix[2][1] = 1;
	matrix[2][2] = 2;

	matrix[0][3] = 4;
	matrix[1][3] = 8;
	matrix[2][3] = 3;
*/




	randinit();

	struct timespec start, end;

	clock_gettime(CLOCK_REALTIME, &start);


	rowReduce(number_of_threads);

	clock_gettime(CLOCK_REALTIME, &end);

	double accum = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
	//printf("elapsed time = %lf \n", accum);

	//printf("Initial Matrix\n");
	//printMatrix();


	// Create B
	
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		B[i] = matrix[i][n];
	}
	dummyMethod4();
	


	// Back Sub
	
	X[n - 1] = B[n - 1] / matrix[n - 1][n - 1];
	dummyMethod3();
	for (i = (n - 2); i >= 0; i--)
	{
		temp = B[i];
		for (j = (i + 1); j < n; j++)
		{
			temp -= (matrix[i][j] * X[j]);
		}
		X[i] = temp / matrix[i][i];
	}
	dummyMethod4();
	
	//printf("Final Matrix:\n");
	//printMatrix();

	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		double prod = 0.0;
		for (j = 0; j < n; j++)
		{
			prod += copyA[i][j] * X[j];
		}
		Ax[i] = prod;
	}
	dummyMethod4();

	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		X[i] = Ax[i] - normB[i];
		//printf("%f\n", X[i]);
	}
	dummyMethod4();

	// compute l2 norm

	double l2 = 0.0;
	dummyMethod3();
	for (i = 0; i < n; i++)
	{
		l2 += (X[i] * X[i]);
	}
	dummyMethod4();

	//l2 = sqrt(l2);
	//printf("L2 norm: %.*e\n", l2);


	printf("elapsed time = %lf \n", accum);




	return 0;

} //end main

void rowReduce(int numThreads){
	int i, pivot, row;
	double ratio, temp, max;
	int maxRow;
	
	for(pivot = 0; pivot<n-1; pivot++){
		#pragma omp parallel num_threads(numThreads)
			max = matrix[pivot][pivot]; //*(*(matrix + pivot) + pivot)
			maxRow = pivot;
			for (i = pivot+1; i < n; i++){
				temp = matrix[i][pivot]; //(*(*(matrix + i) + pivot)
				if (temp > max){
					max = temp;
					maxRow = i;
				}
			}
			swapRows(pivot, maxRow);
			
			
			for (row = pivot + 1 ; row < n; row ++){
				ratio = matrix[row][pivot] / matrix[pivot][pivot];
							dummyMethod1();
				#pragma omp parallel for
				for (i = pivot; i < n + 1; i++){
					matrix[row][i] -= ratio * matrix[pivot][i];
				}
							dummyMethod2();
			}

	}





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