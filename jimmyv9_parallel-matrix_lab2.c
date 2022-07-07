//Joao Pedro Veloso
//COMP 380: Parallel and Distributed Systems
//Professor Larkins
//Program #2

#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <math.h> //sqrt, pow
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//initialize matrices
void init2d(double **p, int size, double base) {
    int i, j;
    *p = (double*) malloc(size*size*sizeof(double));
dummyMethod1();
    #pragma omp parallel for private(j)
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            *(*p + i*size + j) = base*(i+(0.1*j));
        }
    }
dummyMethod2();
    return;
}

//computes A * B = C. Loop ordering = ijk
void mxm_ijk(double *A, double *B, double *C, int size) {
    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for private(k, j)
    for(i = 0; i < size; i++) {
	ii = i * size;
        for(j = 0; j < size; j++) {
            for(k = 0; k < size; k++) {
                C[ii+j] += A[ii+k]*B[k*size+j];
            }
        }
    }
							dummyMethod2();
    return;
}

//computes A * B = C. Loop ordering = ikj
void mxm_ikj(double *A, double *B, double *C, int size) {
    int i, j, k, ii;
							dummyMethod1();
    #pragma omp parallel for private(j, k)
    for(i = 0; i < size; i++) {
	ii = i * size;
        for(k = 0; k < size; k++) {
            for(j = 0; j < size; j++) {
                C[ii+j] += A[ii+k]*B[k*size+j];
            }
        }
    }
							dummyMethod2();
    return;
}

//computes A * B = C. Loop ordering = jki
void mxm_jki(double *A, double *B, double *C, int size) {
    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for private(i, k)
    for(j = 0; j < size; j++) {
        for(k = 0; k < size; k++) {
            for(i = 0; i < size; i++) {
                *(C + i*size + j) += A[i*size+k]*B[k*size+j];
            }
        }
    }
							dummyMethod2();
    return;
}

//same as mxm_ijk(), except it transposes indices that iterate over B
void mxm2(double *A, double *B, double *C, int size) {
    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for private(k, j)
    for(i = 0; i < size; i++) {
	ii = i * size;
        for(j = 0; j < size; j++) {
            for(k = 0; k < size; k++) {
                C[ii+j] += A[ii+k]*B[j*size+k];
            }
        }
    }
							dummyMethod2();
    return;
}

//computes transpose of matrix M
void mmT(double *M, int size) {
    int i, j, ii;
    double sub;
							dummyMethod1();
    #pragma omp parallel for private(sub, i, j)
    for(i = 0; i < size; i++) {
	ii = i * size;
        for(j = 0; j < i; j++) {
            sub = M[ii+j];
            M[ii+j] = M[j*size+i];
            M[j*size+i] = sub;
        }
    }
							dummyMethod2();
    return;
}

//computes Frobenius norm of a 2D matrix M
double normf(double *M, int size) {
    int i, j;
    double ans = 0;
							dummyMethod3();
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ans += pow(*(M + i*size + j), 2);
        }
    }
							dummyMethod4();
    return sqrt(ans);
}

//prints matrix
void print_matrix(double *p, int row, int col) {
    if (row > 4 || col > 4) {
        return;
    }
    
    int i, j;
    
							dummyMethod3();
    for(i = 0; i < row; i++) {
        printf("|");
        for (j = 0; j < col; j++) {
            printf(" %.2f ", *(p + i*col + j));
        }
        printf("|\n");
    }
							dummyMethod4();
    
    //Calculate Frobenium Norm
    double frob_norm = normf(p, row);
    printf("norm:   %.3f\n\n", frob_norm);
    return;
}

int main(int argc, const char *argv[]) {
    int s;
    
    switch(argc) {
    case 3:
        omp_set_num_threads(atoi(argv[2]));
        s = atoi(argv[1]);
        break;
    case 2:
        omp_set_num_threads(1);
        s = atoi(argv[1]);
        break;
    default:
        omp_set_num_threads(1);
        s = 10;
    }
    
    printf("using matrix/vector size of %d\n", s);
    
    double* a = NULL;
    double* b = NULL;
    double* c = NULL;
    
    double start, end;
    
    //INITIALIZING A, B, C
    start = get_wctime();
    init2d(&a, s, 1);
    init2d(&b, s, 2);
    init2d(&c, s, 0);
    printf("initialized matrices and vectors:\n");
    
    //PRINTING INITIAL VECTORS
    if (s < 4) {
        printf("matrix A:\n");
        print_matrix(a, s, s);
        printf("matrix B:\n");
        print_matrix(b, s, s);
        printf("matrix C:\n");
        print_matrix(c, s, s);
    }
    
    
    //A * B = C. ijk
    printf("Computing C = A * B (mxm)\n");
    double start = omp_get_wtime();
    mxm_ijk(a, b, c, s);
    double end = omp_get_wtime();
    ms = (end - start)*1000;
    printf("matrix/matrix multiplication:  %fms\n", ms);
    if (s < 4) {
        printf("matrix C:\n");
        print_matrix(c, s, s);
    }
    
    //A * B = C. ikj
    printf("Computing C = A * B (mxm)\n");
    start = omp_get_wtime();
    mxm_ikj(a, b, c, s);
    end = omp_get_wtime();
    ms = (end - start)*1000;
    printf("matrix/matrix multiplication:  %fms\n", ms);
    if (s < 4) {
        printf("matrix C:\n");
        print_matrix(c, s, s);
    }
    
    //A * B = C. jki
    printf("Computing C = A * B (mxm)\n");
    start = omp_get_wtime();
    mxm_jki(a, b, c, s);
    end = omp_get_wtime();
    ms = (end - start)*1000;
    printf("matrix/matrix multiplication:  %fms\n", ms);
    if (s < 4) {
        printf("matrix C:\n");
        print_matrix(c, s, s);
    }
    
    
    //COMPUTING TRANSPOSE OF B
    printf("Computing B'\n");
    start = omp_get_wtime();
    mmT(b, s);
    end = omp_get_wtime();
    ms = (end - start)*1000;
    printf("matrix transpose:  %fms\n", ms);
    if (s < 4) {
        printf("matrix B:\n");
        print_matrix(b, s, s);
    }
    
    
    
    //A * B = C
    printf("Computing C = A * B (mxm)\n");
    init2d(&c, s, 0);
    start = get_wtime();
    mxm2(a, b, c, s);
    end = get_wctime();
    ms = (end - start)*1000;
    printf("matrix/matrix multiplication:  %fms\n", ms);
    if (s < 4) {
        printf("matrix C:\n");
        print_matrix(c, s, s);
    }
    
    free(a);
    free(b);
    free(c);
    
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