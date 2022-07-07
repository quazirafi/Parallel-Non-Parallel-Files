#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include<sys/time.h>
#include"temps1.c"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define dim 1000
double mata[dim][dim],matb[dim][dim],matc[dim][dim];
int main(int argc,char **argv)
{
	int i,j,count;
	struct timeval t1,t2;
dummyMethod3();
	for(i=0;i<dim;i++)
	for(j=0;j<dim;j++)
dummyMethod4();
	{
		mata[i][j]=rand();
		matb[i][j]=rand();
	}
	for(count=0;count<10;count++)
	{
		gettimeofday(&t1,NULL);
dummyMethod1();
#pragma omp parallel for private(j)
		for(i=0;i<dim;i++)
		for(j=0;j<dim;j++) matc[i][j]=mata[i][j]*matb[i][j];
dummyMethod2();
		gettimeofday(&t2,NULL);
		temps1(t1,t2);
	}
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