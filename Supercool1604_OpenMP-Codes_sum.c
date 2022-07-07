#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int arr[1000000];
int main(int argc, char* argv[]) 
{  
	int sum=0;
dummyMethod3();
	for(int i=0;i<1000000;i++)
	{
		arr[i] = 1;
	}
dummyMethod4();
	double t1 = omp_get_wtime();
dummyMethod1();
    	#pragma omp parallel for reduction(+:sum)
		for(int j=0;j<1000000;j++)
                	sum+=arr[j]; 
	 
	printf("%d",sum);
dummyMethod2();
	double t2 = omp_get_wtime();
	printf("\n%f",t2-t1);

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