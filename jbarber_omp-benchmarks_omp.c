// gcc -fopenmp -O3 -g -std=c99 omp.c -o omp
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define X_SIZE 1000
#define Y_SIZE 1000
#define Z_SIZE 1000
#define TRANS(z,y,x) (x + y * Y_SIZE + z * Z_SIZE * Y_SIZE)

typedef int element;

element * alloc_mat (const unsigned int x, const unsigned int y, const unsigned int z) {
    const size_t size = sizeof(element) * x * y * z;
    element *mat = malloc(size);
#ifdef VERBOSE
    fprintf(stderr, "Size of malloc: %likb\n", size / 1024);
#endif
    if (mat == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    return mat;
}

void free_mat (element *mat) {
    free(mat);
}

int main (int argc, char **argv) {
    element *src_mat = alloc_mat(X_SIZE, Y_SIZE, Z_SIZE);
    element *tar_mat = alloc_mat(X_SIZE, Y_SIZE, Z_SIZE);

    memset(src_mat, 0x1, sizeof(element) * X_SIZE * Y_SIZE * Z_SIZE);
    memset(tar_mat, 0x0, sizeof(element) * X_SIZE * Y_SIZE * Z_SIZE);

    int i, j, k;
							dummyMethod1();
    #pragma omp parallel for shared(tar_mat) private(i,j,k) schedule(static,100)
    for (i = 0; i < X_SIZE; i++) {
        for (j = 0; j < Y_SIZE; j++) {
            for (k = 0; k < Z_SIZE; k++) {
#ifdef DEBUG
                printf("x:%i y:%i z:%i offset:%i\n", i, j, k, TRANS(i,j,k));
#endif
                tar_mat[TRANS(i,j,k)] = src_mat[TRANS(i,j,k)];
            }
        }
    }
							dummyMethod2();

    free_mat(src_mat);
    free_mat(tar_mat);
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