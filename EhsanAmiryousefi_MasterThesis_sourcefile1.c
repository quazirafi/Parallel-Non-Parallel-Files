#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 128

int A[N][N], B[N][N], C[N][N];

int main(int argc, char const *argv[])
{
	int i=0, j=0, k=0;

dummyMethod1();
	#pragma omp parallel for 
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			for(k=0; k<N; k++) {
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}
dummyMethod2();

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