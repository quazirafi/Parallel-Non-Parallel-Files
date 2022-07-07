#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
	int i,n=10;
dummyMethod1();
	#pragma omp parallel for 
	 for(i=0;i<n;i++)
		printf("i : %d \t THREAD : %d\n",i,omp_get_thread_num());
dummyMethod2();
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