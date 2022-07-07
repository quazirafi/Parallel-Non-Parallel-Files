#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(){
	double pi,x;
	int i,N;
	pi=0.0;
	N=1000;
dummyMethod1();
	#pragma omp parallel for private(x) reduce(+:pi)
	for(i=0;i<N;i++){
		x=(double)i/N;
		//#pragma omp atomic
		pi+=4/(1+x*x);
	}
dummyMethod2();
	pi=pi/N;
	printf("Pi is %f\n",pi);
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