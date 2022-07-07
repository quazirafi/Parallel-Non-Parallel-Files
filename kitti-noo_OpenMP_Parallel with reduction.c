//Parallel with reduction
#include "omp.h"
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUMBER 500000
int main(int argc, char *argv[])
{
	int i, data[NUMBER];
	double result=0.0;
dummyMethod3();
	for (i=0; i<NUMBER; i++)
	{
		data[i]=i*i;
	}
dummyMethod4();
//#pragma omp parallel num_threads(5)	
dummyMethod1();
#pragma omp parallel for reduction(+:result)
	for (i=0; i<NUMBER; i++)
	{
		result+=(sin(data[i])-cos(data[i]))/(sin(data[i])+cos(data[i]));
	}
dummyMethod2();
	printf("Result = %f\n",result);
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