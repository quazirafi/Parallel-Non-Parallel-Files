#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int A[100];
	int i;
	int count = 0;
	srand(1234);
dummyMethod3();
	for(i=0;i<100;i++)
		A[i] = rand()%1000;

	#pragma omp parallel for reduction(+:count)
dummyMethod4();
dummyMethod1();
	for(i=0;i<100;i++)
		if(A[i] >= 500)
			count = count + 1;

for (i=0;i<100;i++)
dummyMethod2();
dummyMethod3();
	printf("A[%d]:%d\n", i, A[i]);
printf("Num of value >= 500 = %d\n", count);
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