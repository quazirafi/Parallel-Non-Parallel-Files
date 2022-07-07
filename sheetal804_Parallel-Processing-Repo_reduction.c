#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
	int i,n,chunk;
	float a[100],b[100],result;
	n=10;	
	chunk=2;
	result=0.0;
dummyMethod3();
	for(i=0;i<n;i++){
		a[i]=i*1.0;
		b[i]=i*2.0;
	}
dummyMethod4();
dummyMethod1();
	#pragma omp parallel for \
	default(shared) private(i) \
	schedule(static,chunk) \
	reduction(+:result)
	for(i=0;i<n;i++){
		result=result+(a[i]*b[i]);
		printf("result :%.2f\t i :%d \tTHREAD :%d\t a :%.2f\tb :%.2f\t\n",result,i,omp_get_thread_num(),a[i],b[i]);
	}
dummyMethod2();
	printf("FINAL RESULT :%.2f\n",result);
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