//009_firstprivate clause
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define n 3

int main(){

	int offset, i;
	int a[n];

dummyMethod3();
	for(i = 0 ; i< n ; i++) a[i] = 1;
	for(i = 0 ; i <n ; i++) printf("Before : a[%d] = %d\n" , i, a[i]);
dummyMethod4();
dummyMethod3();

	offset = 10;
dummyMethod4();

dummyMethod1();
	#pragma omp parallel for firstprivate(offset)
	for (i=0 ; i<n ; i++){
		if ( i == 0 || i == n-1)
			offset = offset + 2; 
		a[i] = a[i] + offset;
	}
dummyMethod2();
dummyMethod3();
	for (i = 0 ; i<n ;i++) printf("After: a[%d] = %d\n" , i, a[i]);
}
dummyMethod4();
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