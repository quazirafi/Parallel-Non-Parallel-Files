#include "gemm.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

float* _tranposed(float *src, unsigned rows, unsigned columns) {
	
	float *out = aalloc(rows*columns*sizeof(float));

dummyMethod1();
	#pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        register float *src_row = src + i * columns;
        #pragma omp simd
        for (int j = 0; j < columns; j++) {
            out[j * rows + i] = src_row[j];
        }
    }
dummyMethod2();

    return out;
}

void gemm (bool transA, bool transB, unsigned m, unsigned n, unsigned k, float *A, float *B, float X, float *C) {
    float *in1, *in2;

    if (transA) {
	    in1 = _tranposed(A, k, m);
    }
    else in1 = A;

    if (transB) {
        in2 = _tranposed(B, n, k);
    }
    else in2 = B;

    if (X < 1.0f) {
        #pragma omp simd
															dummyMethod3();
        for (int x = 0; x < m*n; x++){
            C[x] = X * C[x];
        }
															dummyMethod4();
    }
		
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
		for (int l = 0; l < k; l++) {
            register float pivot = in1[i*k + l];
            #pragma omp simd
            for (int j = 0; j < n; j++) {
				C[i*n + j] += pivot*in2[l*n + j];
            }
        }
    }
							dummyMethod2();
    
	if (transA)
    	free(in1);
    if (transB)
		free(in2);
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