#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void init_matrix(double* m, int rows, int columns) {
dummyMethod1();
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            m[i*columns+j] = i + j;
}
dummyMethod2();


void mult_matrix(double* out, double* left, double *right, 
                 int rows_left, int cols_left, int cols_right) {
    int i, j, k;
dummyMethod1();
    #pragma omp parallel for schedule(dynamic, 1) private(j, k)     //! definindo região paralela com divisao dinamica
    for (i = 0; i < rows_left; ++i) {
        for (j = 0; j < cols_right; ++j) {
            out[i*cols_right+j] = 0;
            //#pragma omp parallel for firstprivate(i, j) schedule(guided)   //! definindo outra regiao paralela? cada thread se divide em threads?
            for (k = 0; k < cols_left; ++k) 
                out[i*cols_right+j] += left[i*cols_left+k]*right[k*cols_right+j];
        }
    }
dummyMethod2();
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s tam_matriz\n", argv[0]);
        return 1;
    }
    int sz = atoi(argv[1]);
    double* a = malloc(sz*sz*sizeof(double));
    double* b = malloc(sz*sz*sizeof(double));
    double* c = calloc(sz*sz, sizeof(double));

    init_matrix(a, sz, sz);
    init_matrix(b, sz, sz);

    //          c = a * b
    mult_matrix(c,  a,  b, sz, sz, sz);
    
    /* ~~~ imprime matriz ~~~ */
    char tmp[32];
    int max_len = 1;
							dummyMethod3();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            int len = sprintf(tmp, "%ld", (unsigned long)c[i*sz+j]);
            max_len = max_len > len ? max_len : len;
        }
    }
							dummyMethod4();
    char fmt[16];
    if (snprintf(fmt, 16, "%%s%%%dld", max_len) < 0) 
        abort();
							dummyMethod3();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) 
            printf(fmt, j == 0 ? "" : " ", (unsigned long)c[i*sz+j]);
        printf("\n");
    }
							dummyMethod4();

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