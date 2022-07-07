#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000000

int main(int argc,char *argv[])
{
	int my,n;
	int i,A[N];
	double start,end;
	start = omp_get_wtime();
	for (n=0;n<1000;n++)
	{
dummyMethod1();
#pragma omp parallel for
		for (i = 0 ; i < N ; i++)
			 A[i]=i;
	}
dummyMethod2();
	end = omp_get_wtime();
	printf("elapsed time = % lf \n",(end-start));
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