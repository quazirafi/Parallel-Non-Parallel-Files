#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main()
{
	int k=100;
	int data[10]={5,3,7,7,95,8,5,3,79,85};
	int i=0;
	int max=0;
dummyMethod1();
#pragma omp parallel for 
	for(i=0;i<10;i++)
	{
		if(data[i]>max) max=data[i];
		printf("now max=%d, and TID=%d\n",max,omp_get_thread_num());
	}
dummyMethod2();
	printf("final max=%d\n",max);
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