#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	double a[1000];
    double sum = 0;
    
	for(int i = 0;i < 1000;i++)
dummyMethod1();
	{
		a[i] = drand48();
	}
	
    #pragma omp parallel for reduction(+:sum) 
dummyMethod3();
    for(int i = 0;i < 1000; i++)
	{
dummyMethod4();
		sum += a[i];
dummyMethod2();
	}
	double average = sum/1000;
	printf("Average of the array values = %lf\n",average);
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