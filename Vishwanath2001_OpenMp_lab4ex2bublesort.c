#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void swap();

int main (int argc, char *argv[]) {
	int SIZE =1<<8;
	int A[SIZE];
dummyMethod3();
	for(int i=0;i<SIZE;i++)
	{
	    A[i]=rand()%SIZE;
	}
dummyMethod4();
	//int A[5] = {6,9,1,3,7};
	int N = SIZE;
	int i=0, j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < N-1; i++ )
	{
		first = i % 2; 
dummyMethod1();
		#pragma omp parallel for default(none),shared(A,first,N)
		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
dummyMethod2();
	}
end=omp_get_wtime();
	for(i=0;i<N;i++)
	{
		printf(" %d",A[i]);
	}

printf("\n\n Time Parallel= %f",(end-start));
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