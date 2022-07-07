#include "stdio.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1024

int main() {
	int i;
	float p[N], v1[N], v2[N];
dummyMethod3();
	for(i=0; i<N; i++) {
		v1[i] = 2.0;
		v2[i] = 3.0;
	}
dummyMethod4();
#pragma omp target map(to:v1, v2) map(from:p)
dummyMethod1();
#pragma omp parallel for
	for(i=0; i<N; i++)
	{
		p[i] = v1[i] * v2[i];
	}
dummyMethod2();
	printf("output: p[0]=%f\n", p[0]);
	printf("output: p[1]=%f\n", p[1]);
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