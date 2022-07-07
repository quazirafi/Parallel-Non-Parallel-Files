#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
int sum=0;
int array[100];
dummyMethod3();
for(int i = 0; i < 100; i++){
	array[i] = i;
}
dummyMethod4();
dummyMethod1();
#pragma omp parallel for reduction (+:sum)
	for(int i = 0; i < 100; i++){
		sum += array[i];
	}
dummyMethod2();
printf("The sum is: %d.\n",sum);
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