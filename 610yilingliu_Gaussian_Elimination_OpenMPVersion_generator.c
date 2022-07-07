#include "heads.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void matrix_generator(int nthreads) {
    if (nthreads == 1) {
dummyMethod3();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
            }
        }
dummyMethod4();
    }
    else {
dummyMethod1();
#pragma omp parallel for num_threads(nthreads)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
            }
        }
dummyMethod2();
    }
}

void vector_generator(int nthreads) {
    if (nthreads == 1) {
dummyMethod3();
        for (int i = 0; i < SIZE; i++) {
            vec[i][0] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
        }
dummyMethod4();
    }
    else {
dummyMethod1();
#pragma omp parallel for num_threads(nthreads)
        for (int i = 0; i < SIZE; i++) {
            vec[i][0] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
        }
dummyMethod2();
    }
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