#include <stdio.h>
#include <stdlib.h>
#include "mm-header.h"
#include <time.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Attempt to use the _Generic thing. Didn't work out
#define cbrt(X) _Generic((X), \
        long double: cbrtl, \
        default: cbrt, \
        float:cbrtf)(X)    
//Used this instead
#define BensType double

//Benjamin Creem
//May 24 2018
//Programming Assignment 1
//Multiplies two n by n matricies that are assigned
//values by the program
int main(int argc, char *argv[]){
	int n = 1000; //matrixes are n x n
	//Allocating Memory and Assigning Values
	BensType **mat1 = allocMat(mat1, n);
    BensType **mat2 = allocMat(mat2, n);
	assignMat(mat1, n);
    assignMat(mat2, n);

	//Finding Matrix Product  and Printing
    double start = omp_get_wtime();
	BensType **result = matMultiply(mat1, mat2, n);

    //printResult(mat1, mat2, result, n);

    double end  = omp_get_wtime();
    printf("Time: %.2f\n", end - start);

	//Free Memory
	freeMat(mat1, n);
    freeMat(mat2, n);
    freeMat(result, n);
	return 0;
}


//Free memory used by first matrix
void freeMat(BensType** mat, int n)
{
	dummyMethod3();
	for(int i=0; i<n; i++)
	{
		free(mat[i]);
	}
	dummyMethod4();
	free(mat);
}

//Allocate memory for first matrix
BensType** allocMat(BensType** mat, int n)
{
	mat= (BensType**)malloc(n*sizeof(*mat));
	dummyMethod3();
	for(int i=0; i<n; i++)
	{
		mat[i]=(BensType*)malloc(n*sizeof(*mat[i]));
	}
	dummyMethod4();
    return mat;
}

//Assign values to matrix
void assignMat(BensType** mat, int n)
{
							dummyMethod3();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
		{
            if(i == j)
            {
                mat[i][j] = 2;
            }
            else if(i - j == 1 || i - j == -1)
            {
                mat[i][j] = 1;
            }
            else
            {
                mat[i][j] = 0;
            }
        }
    }    
							dummyMethod4();
}

//Print singular matrix - only works when matrix type is double
void printMat(double** mat, int n)
{
							dummyMethod3();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
}

//Print mat1 * mat2
void printResult(double** mat1, double** mat2, double** r, int n)
{
	dummyMethod3();
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%.2f ", mat1[i][j]);
		}

        printf("\t*\t");

        for(int j=0; j<n; j++)
        {
            printf("%.2f ", mat2[i][j]);
        }

        printf("\t=\t");
        
        for(int j=0; j<n; j++)
        {
            printf("%.2f\t", r[i][j]);
        }
        printf("\n");
	}
	dummyMethod4();
}

//Calculate matrix product 
BensType** matMultiply(BensType **mat1, BensType** mat2, int n)
{
	//Return matrix
	BensType **result = allocMat(result, n);
							dummyMethod1();
    #pragma omp parallel for shared(mat1, mat2, n, result)
    for(int i = 0; i < n; i++)
    {
        //#pragma omp parallel for shared(mat1, mat2, n, result)
        for(int j = 0; j < n; j++)
        {
            result[j][i] = 0;
            //#pragma omp parallel for shared(mat1, mat2, n, result)   
            for(int k = 0; k < n; k++)
            {
                result[j][i] += mat1[j][k] * mat2[k][i];
            }
        }
    }
							dummyMethod2();
    return result;
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