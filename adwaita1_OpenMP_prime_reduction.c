/*
	Prime number 
	To compile:-
		gcc -fopenmp prime.c
*/

#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ()  
{
   	int n = 99999;
	int i = 0,j = 0;
	int cnt=0;
	double start_time;

	// Start timer
	start_time = omp_get_wtime();
	
	dummyMethod1();
	#pragma omp parallel for private(j) reduction(+:cnt)
	for(i=2;i<n;i++)
   	{
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				break;
			}			
		}
		if(i==j)
		{
			cnt++;
		}
   	}
	dummyMethod2();
   	printf("\n Total number of primes found = %d\n", cnt);
   	printf("\n Execution time = %lf seconds\n", omp_get_wtime() - start_time);
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