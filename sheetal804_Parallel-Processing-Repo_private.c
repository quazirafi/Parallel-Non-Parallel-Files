#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
	int a,i,n=10;
dummyMethod1();
	#pragma omp parallel for private(i) lastprivate(a)
		for(i=0;i<n;i++){
			a=i+1;
			printf("THREAD :%d\ti :%d\ta :%d\n",omp_get_thread_num(),i,a);
		}
dummyMethod2();
	printf("a :%d\n",a);
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