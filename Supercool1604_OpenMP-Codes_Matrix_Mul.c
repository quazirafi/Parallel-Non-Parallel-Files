#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define mSize 512

int main(int argc, char* argv[]) 
{	
	double A[mSize][mSize], B[mSize][mSize], C[mSize][mSize];
	  
	int sum=0;
dummyMethod3();
	for(int i=0;i<mSize;i++)
	{
		for(int j=0;j<mSize;j++)
		{
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 0;
		}
	}
dummyMethod4();
	double t1 = omp_get_wtime();
dummyMethod1();
    	#pragma omp parallel for collapse(2)
		for(int i=0;i<mSize;i++)
			for(int j=0;j<mSize;j++)
				for(int k=0;k<mSize;k++)
					C[i][j] += (A[i][k] *B[k][j]);
	for(int i=0;i<mSize;i++)
dummyMethod2();
dummyMethod3();
	{
		for(int j=0;j<mSize;j++)
		{
			printf("%f ",C[i][j]);
		}
		printf("\n");
	}
dummyMethod4();
		
	double t2 = omp_get_wtime();
	printf("\n TIME : %f",t2-t1);

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