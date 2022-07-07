//
// Created by Alex Malogulko on 13/01/2020.
//
//
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include "omp.h"
#include "utils.c"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double ijk_row_sum_partition(double *matrix_a,
                             double *matrix_b,
                             int partition_num,
                             int partition_size,
                             int matrix_size) {
    int partition_start = partition_num * partition_size;
    int next_partition_start = (partition_num + 1) * partition_size;
    double local_max_sum = 0;
dummyMethod3();
    for (int i = partition_start; i < next_partition_start; i++) {
        double row_sum = 0;
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                row_sum += *(matrix_a + i * matrix_size + k) * *(matrix_b + j * matrix_size + k);
            }
        }
        if (local_max_sum < row_sum) {
            local_max_sum = row_sum;
        }
    }
dummyMethod4();
    return local_max_sum;
}

void ijk_row_sum_partitioned(double *matrix_a,
                             double *matrix_b,
                             double *inf_norm,
                             int matrix_size,
                             int num_partitions) {
    check_partition(matrix_size, num_partitions);
    int partition_size = matrix_size / num_partitions;
    double inf_norm_val = 0.;
							dummyMethod1();
#pragma omp parallel for reduction (max: inf_norm_val)
    for (int p_num = 0; p_num < num_partitions; p_num++) {
        inf_norm_val = ijk_row_sum_partition(matrix_a, matrix_b, p_num, partition_size, matrix_size);
        //printf("thread id = %d and p_num = %d inf_norm_val = %f\n", omp_get_thread_num(), p_num, inf_norm_val);
    }
							dummyMethod2();
    //printf("inf norm is %f\n", inf_norm_val);
    *inf_norm = inf_norm_val;
}

/**
 * 4x4 matrix represented in memory as:
 *
 * 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
 *
 * Matrices A and C are stored in row-wise format:
 *
 * 01 02 03 04
 * 05 06 07 08
 * 09 10 11 12
 * 13 14 15 16
 *
 * At the same time, matrix B blocks stored in column-wise format:
 *
 * 01 05 09 13
 * 02 06 10 14
 * 03 07 11 15
 * 04 08 12 16
 *
 */
int main(int argc, char *argv[]) {
    int size, num_partitions;
    struct timespec start, end;
    // Uncomment this if you want the matrices to be actually random
    //srand(time(0));
    parse_args(argc, argv, &size, &num_partitions);
    double *matrix_a = matrix_malloc(size);
    double *matrix_b = matrix_malloc(size);
    double *inf_norm = malloc(sizeof(double));
    // Initialize info objs
    struct matrixInfo matrix_a_info = {.size = size, .mxPtr = matrix_a};
    struct matrixInfo matrix_b_info = {.size = size, .mxPtr = matrix_b};
    struct matrixInfo *matrices_to_randomize[2];
    matrices_to_randomize[0] = &matrix_a_info;
    matrices_to_randomize[1] = &matrix_b_info;

    omp_set_num_threads(num_partitions);

							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < 2; ++i) {
        // printf("thread id = %d, filling matrix %d\n", omp_get_thread_num(), i);
        random_matrix(matrices_to_randomize[i]);
    }
							dummyMethod2();

    //printf("Filled matrices\n");

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    ijk_row_sum_partitioned(matrix_a, matrix_b, inf_norm, size, num_partitions);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000; // microseconds
    printf("%d;%d;%llu\n", size, num_partitions, delta_us);
    free(matrix_a);
    free(matrix_b);
    free(inf_norm);
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