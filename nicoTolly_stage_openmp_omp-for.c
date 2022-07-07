#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char ** argv){
dummyMethod1();
#pragma omp parallel for ordered
	for (int i =0; i<12; i++){
		for (int j =0; j<12; j++){
			printf("non ordered, i=%d, j=%d\n", i, j);
			sleep(1/((i*j)+1));
#pragma omp ordered
dummyMethod2();
			printf("ordered, i=%d, j=%d\n", i, j);
		}
	}
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