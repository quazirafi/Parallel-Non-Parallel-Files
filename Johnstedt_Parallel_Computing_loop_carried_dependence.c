#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[]) 
{

	int thread_count = strtol(argv[1], NULL, 10);

	int n = 50;
	int a[50];

dummyMethod1();
	#pragma omp parallel for num_threads(thread_count)
	for(int i = 0; i < n; i++)
	{
		a[i] =  0.5*i*(i+1);
	}
dummyMethod2();

	
dummyMethod3();
	for (int i = 1; i < n; i++){		
		printf(" %d ", a[i]);
	}
dummyMethod4();

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