#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void compute(double **a, double **b, double **c, double **d, int N, int num_threads) {
dummyMethod1();
    #pragma omp parallel for num_threads(num_threads)
	for (int i = 0; i < N; i++) {
		for (int j = 0 ; j < N-1; j++) {
            a[i][j] =  2 * c[i][j];
			d[i][j] = 2 * c[i][j+1] * b[i][j+1] + c[i][j] ;
		}
        a[i][N-1] = 2 * c[i][N-1];
        d[i][N-1] = 2 * c[i][N-1] * b[i][N-1];
	}
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