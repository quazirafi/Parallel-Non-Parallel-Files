#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int i;
	int res = 0;
	int * a = (int *) calloc(10000000, sizeof(int));
dummyMethod1();
#pragma omp parallel for reduction(+:res)
	for (i = 0; i < 10000000; i++){
		res = res + a[i];
	}
dummyMethod2();
	printf("result is %d", res);
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