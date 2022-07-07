#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 2000
#define BLOCK_NUM 50
#define BLOCK_SIZE N/BLOCK_NUM
#define FactorIntToDouble 1.1;
#define NUM_THREADS 4

double A[N][N], B[N][N], C[N][N];

void initMatrix()
{
	int i, j = 0;
dummyMethod3();
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = ( rand() % 10 ) * FactorIntToDouble;
			B[i][j] = ( rand() % 10 ) * FactorIntToDouble;
		}
	}
dummyMethod4();
}

void matrixMultiply() {
    
	for (int k2 = 0; k2 < N; k2+=BLOCK_SIZE) {
		for (int i2 = 0; i2 < N; i2+=BLOCK_SIZE) {
			for (int j2 = 0; j2 < N; j2+=BLOCK_SIZE) {
				//inside each block
							dummyMethod1();
#pragma omp parallel for num_threads(NUM_THREADS)
				for (int k = k2; k < k2+BLOCK_SIZE; k++) {
					for (int i = i2; i < i2+BLOCK_SIZE; i++) {
						for (int j = j2; j < j2+BLOCK_SIZE; j++) {
							C[i][j] = A[i][k] * B[k][j];
						}
					}
				}
							dummyMethod2();

			}
		}
	}
}

int main()
{
	initMatrix();

	double time_spent = 0.0;
	clock_t begin = clock();

	matrixMultiply();

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time elpased is %f seconds\n", time_spent);

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