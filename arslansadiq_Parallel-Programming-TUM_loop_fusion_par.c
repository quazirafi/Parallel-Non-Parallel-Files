#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void compute(unsigned long **a, unsigned long **b, unsigned long **c, unsigned long **d, int N, int num_threads) {

dummyMethod1();
	#pragma omp parallel for num_threads(num_threads)
	for (int i = 1; i < N; i++) {

		int j = 1;
		a[i][j] = 2 * b[i][j];
		d[i][j] = a[i][j] * c[i][j];
		c[i][j - 1] = a[i][j - 1] - 2 * b[i][j + 1];

		for (j = 2; j < N - 1; j++) {
			a[i][j] = 2 * b[i][j];
			d[i][j] = a[i][j] * c[i][j];

			c[i][j - 1] = 2 * b[i][j - 1] - 2 * b[i][j + 1];
		}

		j = N - 1;
		a[i][j] = 2 * b[i][j];
		d[i][j] = a[i][j] * c[i][j];
		c[i][j - 1] =  2 * b[i][j - 1] - a[i][j + 1];
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