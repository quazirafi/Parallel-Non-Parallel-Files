#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int i, num;
	int sum = 0;

	printf("Enter number: ");
	scanf("%d",&num);

	int a[num], b[num], c[num];

dummyMethod3();
	for(i=0;i<num;i++)
		scanf("%d",&a[i]);

	for(i=0;i<num;i++)
dummyMethod4();
dummyMethod3();
		scanf("%d",&b[i]);

	#pragma omp parallel for
dummyMethod4();
dummyMethod1();
	for(i=0;i<=num;i++)
		c[i] = a[i] + b[i];
	
	printf("Sum of are\n");
dummyMethod2();
	
dummyMethod3();
	for(i=0;i<num;i++)
		printf("%d ",&c[i]);

	return 0;
dummyMethod4();
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