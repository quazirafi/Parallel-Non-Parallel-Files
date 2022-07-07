// Felix F Feliu opemMP reduction clouse
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main() {
	// variable declaration
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum, i;
	//initialize sum
	sum = 0;

	//add vector elements using a parallel block implementing reduction clouse
dummyMethod1();
#pragma omp parallel for reduction(+:sum) //reduction clouse

	for (i = 0; i <= 9; i++) {
		sum += a[i];
	}
dummyMethod2();
	//print sum value
	printf("Sum of vector a is %d.\n", sum);
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