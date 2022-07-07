#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//gcc -g -Wall -fopenmp -o pi piomp.c
long long  n=1000000000;
int main(int argc, char const *argv[]){
	double sum=0.0,pi;
	int k;
	double factor;
	int id=strtol(argv[1],NULL,10);
dummyMethod1();
	#pragma omp parallel for  num_threads(id)\
		reduction(+:sum) private(factor)
		for(k=0;k<n;k++){
			if(k%2==0)
				factor=1.0;
			else
				factor=-1.0;
			sum+=factor/(2*k+1);
		}
dummyMethod2();
	pi=4*sum;
	printf("Pi=%.40f\n",pi);
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