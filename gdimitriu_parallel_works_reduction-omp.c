#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define dim 10
int main(int argc, char **argv)
{
	int vec[dim];
	int i,sum,thread;
	thread=atoi(argv[1]);
dummyMethod3();
	for(i=0;i<dim;i++) vec[i]=i;
	omp_set_num_threads(thread);
dummyMethod4();
	sum=0.0;
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
	for(i=0;i<dim;i++)
		sum=sum+vec[i];
	printf("sum=%d\n",sum);
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