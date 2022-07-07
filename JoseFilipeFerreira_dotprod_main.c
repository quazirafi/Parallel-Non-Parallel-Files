#include "utils.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include <papi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EVENTS 4
int EVENTS[NUM_EVENTS] = {
    PAPI_L2_TCM,
    PAPI_L3_TCM,
    PAPI_LD_INS,
    PAPI_SR_INS
};

int EVENTSET = PAPI_NULL;
long long VALUES[NUM_EVENTS];

#define SIZE 4000
#define MAX_BLOCK_SIDE 12
float A[SIZE][SIZE];
float B[SIZE][SIZE];
float C[SIZE][SIZE];

// order IJK
void dotprod_ijk(
    size_t size, float a[][size], float b[][size], float c[][size]) {
    memset(c, 0, size * size * sizeof(float));

							dummyMethod3();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
							dummyMethod4();
}

void dotprod_ijk_transposed(
    size_t size, float a[][size], float b[][size], float c[][size]) {
    memset(c, 0, size * size * sizeof(float));

    transpose_matrix(size, b);

							dummyMethod3();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
							dummyMethod4();
}

// order IKJ
void dotprod_ikj(
    size_t size, float a[][size], float b[][size], float c[][size]) {
    memset(c, 0, size * size * sizeof(float));

							dummyMethod3();
    for (size_t i = 0; i < size; i++) {
        for (size_t k = 0; k < size; k++) {
            for (size_t j = 0; j < size; j++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
							dummyMethod4();
}

// order JKI
void dotprod_jki(
    size_t size, float a[][size], float b[][size], float c[][size]) {
    memset(c, 0, size * size * sizeof(float));

							dummyMethod3();
    for (size_t j = 0; j < size; j++) {
        for (size_t k = 0; k < size; k++) {
            for (size_t i = 0; i < size; i++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
							dummyMethod4();
}

void dotprod_jki_transposed(
    size_t size, float a[][size], float b[][size], float c[][size]) {
    memset(c, 0, size * size * sizeof(float));

    transpose_matrix(size, a);
    transpose_matrix(size, b);

							dummyMethod3();
    for (size_t j = 0; j < size; j++) {
        for (size_t k = 0; k < size; k++) {
            for (size_t i = 0; i < size; i++) {
                c[j][i] += a[k][i] * b[j][k];
            }
        }
    }
							dummyMethod4();

    transpose_matrix(size, c);
}

// block optimization
void dotprod_ijk_block(
    size_t size, float a[][size], float b[][size], float c[][size]) {

    memset(c, 0, size * size * sizeof(float));

    size_t c_block_size =
        SIZE > MAX_BLOCK_SIDE ? SIZE / (SIZE / MAX_BLOCK_SIDE) : SIZE;

    transpose_matrix(size, b);

							dummyMethod3();
    for (size_t bk = 0; bk < size; bk += c_block_size) {
        for (size_t bj = 0; bj < size; bj += c_block_size) {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = bj; j < bj + c_block_size; j++) {
                    for (size_t k = bk; k < bk + c_block_size; k++) {
                        c[i][j] += a[i][k] * b[j][k];
                    }
                }
            }
        }
    }
							dummyMethod4();
}

void dotprod_ijk_block_vec(
    size_t size,
    float a[__restrict__][size],
    float b[__restrict__][size],
    float c[__restrict__][size]) {

    memset(c, 0, size * size * sizeof(float));

    size_t c_block_size =
        SIZE > MAX_BLOCK_SIDE ? SIZE / (SIZE / MAX_BLOCK_SIDE) : SIZE;

    transpose_matrix(size, b);

							dummyMethod3();
    for (size_t bk = 0; bk < size; bk += c_block_size) {
        for (size_t bj = 0; bj < size; bj += c_block_size) {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = bj; j < bj + c_block_size; j++) {
                    float tmp = 0;
                    for (size_t k = bk; k < bk + c_block_size; k++) {
                        tmp += a[i][k] * b[j][k];
                    }
                    c[i][j] += tmp;
                }
            }
        }
    }
							dummyMethod4();
}

void dotprod_ijk_block_vec_openmp(
    size_t size,
    float a[__restrict__][size],
    float b[__restrict__][size],
    float c[__restrict__][size]) {

    memset(c, 0, size * size * sizeof(float));

    size_t c_block_size =
        SIZE > MAX_BLOCK_SIDE ? SIZE / (SIZE / MAX_BLOCK_SIDE) : SIZE;

    transpose_matrix(size, b);

    for (size_t bk = 0; bk < size; bk += c_block_size) {
        for (size_t bj = 0; bj < size; bj += c_block_size) {
																							dummyMethod1();
#pragma omp parallel for
            for (size_t i = 0; i < size; i++) {
                for (size_t j = bj; j < bj + c_block_size; j++) {
                    float tmp = 0;
                    for (size_t k = bk; k < bk + c_block_size; k++) {
                        tmp += a[i][k] * b[j][k];
                    }
                    c[i][j] += tmp;
                }
            }
																							dummyMethod2();
        }
    }
}

void run_with_PAPI(
    char* name,
    void f(size_t size, float m1[][size], float m2[][size], float r[][size])) {

    printf(">%s\n", name);

    PAPI_start(EVENTSET);
    f(SIZE, A, B, C);
    PAPI_stop(EVENTSET, VALUES);
    assert_result_lines(SIZE, C);

    clear_cache();

    start_timer();
    f(SIZE, B, A, C);
    long long unsigned time = stop_timer();

    assert_result_collums(SIZE, C);

    printf("TIME:%llu\n", time);

    char* event_name = (char*) malloc(sizeof(char) * PAPI_MAX_STR_LEN);
    for (size_t i = 0; i < NUM_EVENTS; i++) {
        PAPI_event_code_to_name(EVENTS[i], event_name);
        printf("EVENT %s\t%lld\n", event_name, VALUES[i]);
    }
    putchar('\n');

    free(event_name);
    PAPI_reset(EVENTSET);

    clear_cache();
}

int main(void) {
    // Initialize PAPI
    PAPI_library_init(PAPI_VER_CURRENT);
    PAPI_create_eventset(&EVENTSET);
    PAPI_add_events(EVENTSET, EVENTS, NUM_EVENTS);

    // Initialize matrices
    matrices_rand_ones(SIZE, A, B);

    // IJK
    run_with_PAPI("ijk", dotprod_ijk);
    run_with_PAPI("ijk transposed", dotprod_ijk_transposed);

    // IKJ
    /* run_with_PAPI("ikj", dotprod_ikj); */

    // JKI
    run_with_PAPI("jki", dotprod_jki);
    run_with_PAPI("jki transposed", dotprod_jki_transposed);

    // BLOCK
    /* run_with_PAPI("ijk block", dotprod_ijk_block); */
    /* run_with_PAPI("ijk block & vec", dotprod_ijk_block_vec); */
    /* run_with_PAPI("ijk block & vec & OpenMP", dotprod_ijk_block_vec_openmp);
     */
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