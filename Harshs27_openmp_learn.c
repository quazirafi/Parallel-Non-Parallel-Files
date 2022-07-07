// learning and verifying concepts in this file .. NOT FOR EVALUATION
#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){
	int i, a=1000;
dummyMethod1();
	#pragma omp parallel for firstprivate(a) lastprivate(a)
	for (i=0;i<10;i++){
		a = a+i;
	}
dummyMethod2();
	printf("Value of a: %d\n", a);
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