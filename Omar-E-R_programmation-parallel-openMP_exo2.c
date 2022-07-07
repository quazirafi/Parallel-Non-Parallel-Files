#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_STEPS 10000
#define NUM_OPS 50

int main()
{
	int num = 0;
dummyMethod1();
	#pragma omp parallel for num_threads(4) reduction(+:num)
	for (int i = 0; i < NUM_STEPS; i++)
	{
		for (int j = 0; j < NUM_OPS; j++)
			num++;
		for (int j = 0; j < NUM_OPS; j++)
			num--;
	}
dummyMethod2();
	printf("num = %d\n", num);
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