#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int i, num;
	num = 100;
	int dot = 0;

	int a[num], b[num], c[num];

dummyMethod3();
	for(i=0;i<num;i++)
		a[i]=num*num%100;

	for(i=0;i<num;i++)
dummyMethod4();
dummyMethod3();
		b[i]=num*num*num%100;

	#pragma omp parallel for
dummyMethod4();
dummyMethod1();
	for(i=0;i<=num;i++)
		c[i] = a[i] * b[i];

	for(i=0;i<=num;i++)
dummyMethod2();
dummyMethod3();
		dot += c[i];
	
	
	printf("Dot Product is %d\n",dot);
dummyMethod4();

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