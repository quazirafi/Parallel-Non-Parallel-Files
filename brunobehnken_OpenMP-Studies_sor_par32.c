#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define TAM 1024
#define M 1024
#define X 799
#define Y 799

double temp[TAM][TAM], mat[TAM][TAM];

void sor(void) {
	int	i,j,k;

	omp_set_num_threads(32);

	for (k = 0; k < M; k++) {
dummyMethod1();
    	#pragma omp parallel for shared(temp,mat) private(j)
		for (i = 1; i < TAM - 1; i++) {  // casas "pretas"
			j = (i%2) ? 1 : 2;
			for(; j < TAM - 1; j+=2) {
				if (i == X && j == Y) continue;
				temp[i][j] = 0.25*(mat[i-1][j] + mat[i+1][j] + mat[i][j-1] + mat[i][j+1]);
			}
		}
dummyMethod2();
		memcpy(mat, temp, sizeof(mat));

			dummyMethod1();
    	#pragma omp parallel for shared(temp,mat) private(j)
		for (i = 2; i < TAM - 1; i++) {  // casas "brancas"
			j = (i%2) ? 2 : 1;
			for(; j < TAM - 1; j+=2) {
				if (i == X && j == Y) continue;
				temp[i][j] = 0.25*(mat[i-1][j] + mat[i+1][j] + mat[i][j-1] + mat[i][j+1]);
			}
		}
			dummyMethod2();
		memcpy(mat, temp, sizeof(mat));
	}
}

void initialize_matrix() {
	int i, j;

	for (i = 0; i < TAM; i++) {
		for(j = 0; j < TAM; j++)
			mat[i][j] = 20;
	}
	mat[X][Y] = 100;
	memcpy(temp, mat, sizeof(mat));
}

int main(int argc, char const *argv[]) {
	initialize_matrix();
	double start = omp_get_wtime();
	sor();
	double end = omp_get_wtime();
	printf("%f\n",end-start);
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