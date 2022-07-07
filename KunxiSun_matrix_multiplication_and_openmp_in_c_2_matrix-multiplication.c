/**
 * Optimized version using openmp
 */

#include <stdio.h>
#include "omp.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void multiply(const float * mata, size_t mata_width, size_t mata_height, const float * matb, size_t matb_width, size_t matb_height, float ** result_mat, size_t * res_width, size_t * res_height) {
    if(result_mat) {
        *res_width = matb_width;
        *res_height = mata_height;
        *result_mat = calloc(mata_height * matb_width, sizeof(float));
        
dummyMethod1();
        #pragma omp parallel for collapse(3)
        for(size_t y = 0; y < mata_height; y++) {
            for(size_t x = 0; x < matb_width; x++) {
                for(size_t k = 0; k < mata_width; k++) {
                    (*result_mat)[(y * matb_width) + x] =(mata[(y * mata_width) + k] * matb[(k * matb_width) + x]);
                }
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