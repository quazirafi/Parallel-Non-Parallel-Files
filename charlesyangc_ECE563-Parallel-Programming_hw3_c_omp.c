#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int i;
	double res;
dummyMethod1();
#pragma omp parallel for reduction(+:res)
	for (i = 1; i <= 10000000; i++){
		res = res + 1 / ((double) i);
	}
dummyMethod2();
	printf("OpenMP, parallel, 1 to 10,000,000, res is %.20f \n", res);

	res = 0.0;
dummyMethod1();
#pragma omp parallel for reduction(+:res)
	for (i = 10000000; i >= 1; i--){
		res = res + 1 / ((double) i);
	}
dummyMethod2();
	printf("OpenMP, parallel, 10,000,000 to 1, res is %.20f \n", res);
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