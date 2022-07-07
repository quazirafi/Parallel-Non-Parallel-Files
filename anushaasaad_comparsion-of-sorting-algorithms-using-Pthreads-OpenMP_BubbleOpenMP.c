#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 1000

void swap();

int main (int argc, char *argv[]) {
	int A[MAX];
	int N=MAX; 
dummyMethod3();
	for(int i=0;i<MAX;i++)
	{
	    A[i]=rand()%500;
	}
dummyMethod4();
	int i=0, j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < MAX; i++ )
	{
		first = i % 2; 
dummyMethod1();
		#pragma omp parallel for default(none),shared(A,first,N)
		for( j = first; j < MAX-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
dummyMethod2();
	}
end=omp_get_wtime();
	for(i=0;i<MAX;i++)
	{
		printf(" %d",A[i]);
	}
	printf("\n"); 

printf("Time taken: %lf",(end-start));
}

void swap(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
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