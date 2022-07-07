#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv) {
	int sum = 0, i = 0;
	int Data[1000] = {0};

dummyMethod3();
	for(i = 0; i < 1000; i++) {
		Data[i] = i+1;
	}
dummyMethod4();

dummyMethod1();
#pragma omp parallel for reduction(+:sum)
	for(i = 0; i < 1000; i++) {
		sum += Data[i];
	}
dummyMethod2();

	printf("Result = %d \n", sum);

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