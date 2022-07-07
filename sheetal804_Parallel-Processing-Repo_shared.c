#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int i,a,n;
	scanf("%d",&n);
dummyMethod1();
	#pragma omp parallel for shared(i,a)
	for(i=0;i<n;i++)
	{
		a=i+1;
		printf("Thread %d has a value of a=%d for i= %d\n",omp_get_thread_num(),a,i);
	}
dummyMethod2();
	printf("a=%d",a);
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