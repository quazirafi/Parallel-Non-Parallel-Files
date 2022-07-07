#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int multiplicarOmp (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int nt) {
    int i, j, k;    
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);
    }
    omp_set_num_threads(nt);

dummyMethod1();
#pragma omp parallel for schedule(dynamic) private(i,j,k) shared(mat_a,mat_b,mat_c)
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			mat_c[i][j] = 0;
			for(k = 0; k < L; k++){
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
			}
        }
    }
        return 0;
}
dummyMethod2();

int multiplicarOmpIKJ(int **mat_a, int **mat_b, int **mat_c, int N, int L, int M, int nt) {
    int i, j, k;    
    if(mat_a == NULL || mat_b == NULL || mat_c == NULL ){
        printf("\nMatriz nao alocada!!!\n");
        exit(1);
    }
omp_set_num_threads(nt);
	dummyMethod1();
#pragma omp parallel for schedule(dynamic) private(i,j,k) shared(mat_a,mat_b,mat_c)
	for(i = 0; i < N; i++){
		for(k = 0; k < L; k++){
			for(j = 0; j < M; j++){
			//mat_c[i][j] = 0;
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
			}
        }
    }
	dummyMethod2();
        return 0;
}
void multiplicaBlocoOMP(int size, int n, int **A, int **B, int **C, int TILE, int nt){
	int i, j, k, x, y, z;
    omp_set_num_threads(nt);

	dummyMethod1();
#pragma omp parallel for schedule(dynamic) private(i,j,k,x,y,z) shared(A,B,C)
	for(i = 0; i < size; i += TILE){
	    for(j = 0; j < size; j += TILE){
	        for(k = 0; k < size; k += TILE){
	            for(x = i; x < i + TILE; x++){
		            for(y = j; y < j + TILE; y++){
		                for(z = k; z < k + TILE; z++){
		                    C[x][y] += A[x][z] * B[z][y];
                        }
                    }
                }
            }
        }
    }
	dummyMethod2();
}
void multiplicaBlocoOMPIKJ(int size, int n, int **A, int **B, int **C, int TILE, int nt){
	int i, j, k, x, y, z;
    omp_set_num_threads(nt);

	dummyMethod1();
#pragma omp parallel for schedule(dynamic) private(i,j,k,x,y,z) shared(A,B,C)
	for(i = 0; i < size; i += TILE){
        for(k = 0; k < size; k += TILE){	    
            for(j = 0; j < size; j += TILE){	        
	            for(x = i; x < i + TILE; x++){
		            for(y = j; y < j + TILE; y++){
		                for(z = k; z < k + TILE; z++){
		                    C[x][y] += A[x][z] * B[z][y];
                        }
                    }
                }
            }
        }
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