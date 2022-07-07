#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main(void){
	int b[3];
	char* cptr;
	int i;
	cptr= malloc(sizeof(char));
dummyMethod1();
	#pragma omp parallel for
	for( i= 0 ; i< 3 ; i++ ){
		printf("%d\n", i);
	}
dummyMethod2();
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