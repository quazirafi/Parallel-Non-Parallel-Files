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
	int sum = 0;
	srand(1234);
dummyMethod3();
	for(i=0;i<100;i++)
		A[i] = rand()%1000;

	#pragma omp parallel for reduction(+:sum)
dummyMethod4();
dummyMethod1();
	for(i=0;i<100;i++)
		sum = sum + A[i];

for (i=0;i<100;i++)
dummyMethod2();
dummyMethod3();
	printf("A[%d]:%d\n", i, A[i]);
printf("Total sum = %d\n", sum);
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