#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	omp_set_num_threads(4);
	const int N = 100;
	int i,k;
	float a[N],b[N],dot_prod=0.0;
dummyMethod3();
	for(k=0;k<N;k++){
		a[k]=3.0*k;
		b[k]=1.8*k;
	}
dummyMethod4();

dummyMethod1();
	#pragma omp parallel for reduction(+:dot_prod)
	for(i=0;i<N;i++){
		dot_prod = dot_prod + a[i] + b[i];
	}
dummyMethod2();
	

	printf("Inner product of a[] and b[] = %f\n",dot_prod);
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