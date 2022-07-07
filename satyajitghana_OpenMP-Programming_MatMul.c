#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int min(int a, int b) { return a < b ? a : b; }
void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C ) {


    int i, j, k, ii, jj, kk;

    i = j = k = ii = jj = kk = 0;

    int block_size = b;

    double temp;
dummyMethod1();
#pragma omp parallel for schedule(static) collapse(2) private(i, j)
    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            C[i * p + j] *= beta;
        }
    }
dummyMethod2();

#pragma omp parallel default(shared) private(i, j, k, ii, jj, kk, temp)
#pragma omp for schedule(static) collapse(2)
							dummyMethod3();
    for (jj = 0; jj < p; jj += block_size) {
        for (kk = 0; kk < n; kk += block_size) {
            for (i = 0; i < m; i++) {
                for (j = jj;
                     j < ((jj + block_size) > p ? p : (jj + block_size)); j++) {
                    temp = 0.0f;
                    for (k = kk;
                         k < ((kk + block_size) > n ? n : (kk + block_size));
                         k++) {
                        temp += alpha * A[k * m + i] * B[k * p + j];
                    }
                    C[i * p + j] += temp;
                }
            }
        }
    }
							dummyMethod4();

    // int chunk = 1;
    // // Do block matrix multiplication
    // for (k = 0; k < n; k += block_size)
    //     for (j = 0; j < p; j += block_size)
    //         for (i = 0; i < m; ++i)
    //             for (jj = j; jj < min(j + block_size, p); ++jj) {
    //               C[i*p + jj] *= beta;
    //                 for (kk = k; kk < min(k + block_size, n); ++kk)
    //                   C[i*p + jj] += alpha*A[kk*m+ii] * B[kk*p+jj];

    // for (i = 0 ; i < m ; i++) {
    //   for (j = 0 ; j < p ; j++) {
    //     C[i*p+j] *= beta;
    //     for (k = 0 ; k < n ; k++) {
    //       C[i*p+j] += alpha * A[k*m+i] * B[k*p+j];
    //     }
    //   }
    // }

    // #pragma omp parallel default(shared) private(i, j, k, ii, jj, kk, temp)
    // #pragma omp for schedule(static)
    // for (jj = 0; jj < p; jj += b) {
    //     for (kk = 0; kk < n; kk += b) {
    //         for (i = 0; i < m; i++) {
    //             for (j = jj; j < ((jj + b) > p ? p : (jj + b)); j++) {
    //                 C[i * p + j] *= beta;
    //                 for (k = kk; k < ((kk + b) > n ? n : (kk + b)); k++) {
    //                     // temp += alpha * A[k*m+i]*B[k*p+j];
    //                     C[i * p + j] += alpha * A[k * m + i] * B[k * p + j];
    //                 }
    //                 // C[i*p+j] = temp;
    //             }
    //         }
    //     }
    // }

    // Basic Version
    // for (int i = 0 ; i  < m ; i++) {
    //   for (int j = 0 ; j < p ; j++) {
    //     C[i*p+j] *= beta;
    //     for (int k = 0 ; k < n ; k++) {
    //       C[i*p+j] += alpha * A[k*m + i] * B[k*p+j];
    //     }
    //   }
    // }
    // }
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