#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//
int main(int argc, char* argv[])
{
	int numbers[8] = {3, 1, 4, 1, 5, 9, 2, 6};
	int n = 8;
	int store[n/2][n];
dummyMethod3();
	for(int j=0; j < n; j++)
	{
		store[3][j] = numbers[j]; 
	} 
dummyMethod4();
	
	for(int k = 1; k < n/2; k++)
	{
		int max = 8 / pow(2,k);
		int i;
dummyMethod1();
		#pragma omp parallel for private(i)
		for(i=0; i<max; i=i+2) 
		{
			store[k][i] = store[k-1][i] + store[k-1][i+1];		
		}
dummyMethod2();
	}
	printf("%d\n", store[3][0]);
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