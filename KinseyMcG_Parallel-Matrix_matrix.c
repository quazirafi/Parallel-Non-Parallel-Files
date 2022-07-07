#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Function for evaluating runtime
double get_wctime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return(tv.tv_sec + 1E-6 * tv.tv_usec);
}

// Initialize 2D matrix
void init2d(double base, int rowcol, double **arr) {
    *arr = (double *)malloc(rowcol * rowcol * sizeof(double));
dummyMethod3();
    for (int i = 0; i < rowcol; i++) {
        for (int j = 0; j < rowcol; j++) {
            *(*arr + rowcol * i + j) = base * (i + (0.1 * j));
        }
    }
dummyMethod4();
    return;
}

// Initialize 1D vector
void init1d(double base, int size, double **arr) {
    *arr = (double *)malloc(size * size * sizeof(double));
dummyMethod3();
    for (int i = 0; i < size; i++) {
        *(*arr + size * i) = base * (i + 1);
    }
dummyMethod4();
    return;
}

// Matrix multiply, method 1, ijk loop ordering
void mxm(int size, double *a, double *b, double *c) {
    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for private(j, k)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                c[size * i + j] = c[size * i + j] + (a[size * i + k] * b[size * k + j]);
            }
        }
    }
							dummyMethod2();
    return;
}

// Matrix multiply, method 1, jki loop ordering
void mxm_jki(int size, double *a, double *b, double *c) {
    int j, k, i;
							dummyMethod1();
    #pragma omp parallel for private(i, k)
    for (j = 0; j < size; j++) {
        for (k = 0; k < size; k++) {
            for (i = 0; i < size; i++) {
                c[size * i + j] = c[size * i + j] + (a[size * i + k] * b[size * k + j]);
            }
        }
    }
							dummyMethod2();
    return;
}

// Matrix multiply, method 1, ikj loop ordering
void mxm_ikj(int size, double *a, double *b, double *c) {
    int i, k, j;
							dummyMethod1();
    #pragma omp parallel for private(j, k)
    for (i = 0; i < size; i++) {
        for (k = 0; k < size; k++) {
            for (j = 0; j < size; j++) {
                c[size * i + j] = c[size * i + j] + (a[size * i + k] * b[size * k + j]);
            }
        }
    }
							dummyMethod2();
    return;
}

// Matrix multiply, method 2
void mxm2(int size, double *a, double *b, double *c) {
    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for private(j, k)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                c[size * i + j] = c[size * i + j] + (a[size * i + k] * b[size * j + k]);
            }
        }
    }
							dummyMethod2();
    return;
}

// Matrix/vector multiply
void mxv(int size, double *m, double *v, double *r) {
							dummyMethod3();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            r[size * i] = r[size * i] + m[size * i + j] * v[size * j];
        }
    }
							dummyMethod4();
    return;
}

// Matrix transpose
void mmT(int size, double *arr) {
    double temp;
							dummyMethod3();
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            temp = arr[size * i + j];
            arr[size * i + j] = arr[size * j + i];
            arr[size * j + i] = temp;
        }
    }
							dummyMethod4();
    return;
}

// Compute Frobenius Norm
double normf(double *arr, int rowcol) {
    double sum = 0;
    double sqr = 0;
    double norm = 0;
							dummyMethod3();
    for (int i = 0; i < rowcol; i++) {
        for (int j = 0; j < rowcol; j++) {
            sqr = *(arr + rowcol * i + j) * *(arr + rowcol * i + j);
            sum += sqr;
        }
    }
							dummyMethod4();
    norm = sqrt(sum);
    return norm;
}

// Print 2D matrix
void print_matrix(double *arr, int size) {
							dummyMethod3();
    for (int i = 0; i < size; i++) {
        printf("| ");
        for (int j = 0; j < size; j++) {
            printf("%0.2f ", arr[size * i + j]);
        }
        printf("|\n");
    }
							dummyMethod4();

    double norm;
    norm = normf(arr, size);
    printf("norm:    %0.3f\n", norm);
    printf("\n");
    return;
}

// Print 1D vector
void print_vector(double *arr, int size) {
    printf("| ");
							dummyMethod3();
    for (int i = 0; i < size; i++) {
        printf("%0.2f ", arr[size * i]);
    }
							dummyMethod4();
    printf("|\n\n");
    return;
}

int main(int argc, const char * argv[]) {
    double start, end;
    int s = atoi(argv[1]);
    printf("using matrix/vector size of %s\n", argv[1]);
    int cores = atoi(argv[2]);
    printf("core(s): %s\n", argv[2]);
    omp_set_num_threads(cores);

    // init2d and init1d
    double *a, *b, *c = NULL;
    double *v1, *v2 = NULL;
    start = get_wctime();
    init2d(1, s, &a);
    init2d(2, s, &b);
    init2d(0, s, &c);
    init1d(1, s, &v1);
    init1d(0, s, &v2);
    end = get_wctime();
    double msec = (end - start)*1000;

    // print matrices and vectors
    printf("matrix/vector initialization:  %f ms\n", msec);
    printf("initialized matrices and vectors:\n");
    if (s < 5) {
     printf("matrix A:\n");
     print_matrix(a, s);
     printf("matrix B:\n");
     print_matrix(b, s);
     printf("matrix C:\n");
     print_matrix(c, s);
     printf("vector v1:");
     print_vector(v1, s);
     printf("vector v2:");
     print_vector(v2, s);
    }

    // mxm, ijk
    printf("Computing C = A * B (mxm_ijk)\n");
    double begin = omp_get_wtime();
    mxm(s, a, b, c);
    printf("elapsed time: %12.4lf\n", omp_get_wtime() - begin);
    if (s < 5) {
     printf("matrix C:\n");
     print_matrix(c, s);
    }

    // mxm, ikj
    init2d(0, s, &c);
    printf("Computing C = A * B (mxm_ikj)\n");
    begin = omp_get_wtime();
    mxm_ikj(s, a, b, c);
    printf("elapsed time: %12.4lf\n", omp_get_wtime() - begin);
    if (s < 5) {
     printf("matrix C:\n");
     print_matrix(c, s);
    }

    // mxm, jki
    init2d(0, s, &c);
    printf("Computing C = A * B (mxm_jki)\n");
    begin = omp_get_wtime();
    mxm_jki(s, a, b, c);
    printf("elapsed time: %12.4lf\n", omp_get_wtime() - begin);
    if (s < 5) {
     printf("matrix C:\n");
     print_matrix(c, s);
    }

    // mxv
    printf("Computing v2 = B * v1\n");
    start = get_wctime();
    mxv(s, b, v1, v2);
    end = get_wctime();
    msec = (end - start)*1000;
    printf("matrix/vector multiplication:  %f ms\n", msec);
    if (s < 5) {
     printf("vector v2:\n");
     print_vector(v2, s);
    }

    // mmT
    printf("Computing B'\n");
    start = get_wctime();
    mmT(s, b);
    end = get_wctime();
    if (s < 5) {
     printf("matrix B:\n");
     print_matrix(b, s);
    }
    msec = (end - start)*1000;
    printf("matrix transpose:  %f ms\n\n", msec);

    // mxm2
    init2d(0, s, &c);   // reset all values in C to 0 (negate mxm operation)
    printf("Computing C = A * B (mxm2)\n");
    begin = omp_get_wtime();
    mxm2(s, a, b, c);
    printf("elapsed time: %12.4lf\n", omp_get_wtime() - begin);
    if (s < 5) {
     printf("matrix C:\n");
     print_matrix(c, s);
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