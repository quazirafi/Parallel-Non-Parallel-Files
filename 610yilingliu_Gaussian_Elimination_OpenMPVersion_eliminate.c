#include "heads.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void eliminate(int base, int target, int col) {
    double base_num = matrix[base][col];
    double multi = (double)matrix[target][col] / base_num;
    // start from col to reduce time complexity.(item before col is already become 0) 
    if(multi != 0){
dummyMethod3();
        for (int i = col; i < SIZE; i++) {
            // function discussed in readme.md
            matrix[target][i] -= matrix[base][i] * multi;
        }
dummyMethod4();
        vec[target][0] -= vec[base][0] * multi;
    }
}

void eliminate_all(int nthreads) {
    if (nthreads == 1) {
dummyMethod3();
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                eliminate(i, j, i);
            }
        }
dummyMethod4();
    }
    else {
        omp_set_num_threads(nthreads);
        int i, j;
dummyMethod1();
#pragma omp parallel for private(j)
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                eliminate(i, j, i);
            }
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