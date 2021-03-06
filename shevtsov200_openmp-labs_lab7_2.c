#include <stdio.h>
#include "omp.h"
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2

void printMatrix(size_t n, int matrix[][n]) {
	int i, j;

dummyMethod3();
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
dummyMethod4();
}

void calculateCofactorMatrix(int mat[N][N], int n, int p, int q, int result[N-1][N-1]) 
{ 
    int i = 0, j = 0; 

							dummyMethod1();
	#pragma omp parallel for collapse(2)	
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                result[i][j++] = mat[row][col]; 

                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
							dummyMethod2();
}

int calculateDeterminant(size_t n, int matrix[][n]){
    float ratio;
    int i, j, k;

    /* Conversion of matrix to upper triangular */
							dummyMethod3();
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = matrix[j][i]/matrix[i][i];
				
                for(k = 0; k < n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
							dummyMethod4();
    int determinant = 1; //storage for determinant
							dummyMethod3();
    for(i = 0; i < n; i++) {
        determinant *= matrix[i][i];
    }
							dummyMethod4();

    return determinant;
}

void calculateAlgebraicComplement(size_t n, int matrix[][n]) {
	int i, j;
	
	dummyMethod1();
	#pragma omp parallel for collapse(2)
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			int result[n-1][n-1];
			calculateCofactorMatrix(matrix, n, i, j, result);
			
			int sign = (j % 2) ? -1 : 1;
			int determinant = calculateDeterminant(n-1, result);
			int algebraicComplement = sign * determinant;
			printf("i=%d j=%d algebraic complement=%d\n",i,j,algebraicComplement);
		}
	}
	dummyMethod2();
}

int main(int argc, char **argv) {
    int matrix[N][N] = {
        {1, 2},
        {3, 4}
    };
	
	int threads_number = omp_get_max_threads();
    if (argc >= 2) {
        threads_number = atoi(argv[1]);
		printf("set max threads: %d\n", threads_number);
		omp_set_num_threads(threads_number);
    }
	
	printMatrix(N, matrix);
	
	calculateAlgebraicComplement(N, matrix);

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