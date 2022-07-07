/*
============================================================================
Filename    : sharing.c
Author      : Bereyziat/Del Zio
SCIPER		: 282962/311240
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int perform_bucket_computation(int, int, int);

int main (int argc, const char *argv[]) {
    int num_threads, num_samples, num_buckets;

    if (argc != 4) {
		printf("Invalid input! Usage: ./sharing <num_threads> <num_samples> <num_buckets> \n");
		return 1;
	} else {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
        num_buckets = atoi(argv[3]);
	}
    
    set_clock();
    perform_bucket_computation(num_threads, num_samples, num_buckets);

    printf("Using %d threads: %d operations completed in %.4gs.\n", num_threads, num_samples, elapsed_time());
    return 0;
}

int perform_bucket_computation(int num_threads, int num_samples, int num_buckets) {
    int num_samples_per_thread = num_samples/num_threads;
    int histogram[num_buckets];
    int tmp_hist[num_threads][num_buckets];

    /*
     *  better parallelization
     */
							dummyMethod1();
    #pragma omp parallel for shared (tmp_hist)
    for (int i = 0; i<num_threads; i++){
        rand_gen generator = init_rand();
        for(int j = 0; j<num_samples_per_thread; j++){
            int tid = omp_get_thread_num();
            int val = next_rand(generator) * num_buckets;
            tmp_hist[tid][val]++;
        }
        free_rand(generator);
    }
							dummyMethod2();

    //merge loop
							dummyMethod1();
    #pragma omp parallel for shared (tmp_hist, histogram)
    for(int i = 0; i<num_buckets; i++){
        for(int tid = 0; tid < omp_get_thread_num(); tid++){
            histogram[i] += tmp_hist[tid][i];
        }
    }
							dummyMethod2();

    /*
     *  parallelization with true sharing
     */
//    volatile int *histogram = (int*) calloc(num_buckets, sizeof(int));
//
//    int num_samples_per_thread = num_samples/num_threads;
//    #pragma omp parallel for
//    for(int n = 0; n<num_threads; n++){
//        rand_gen generator = init_rand();
//        for(int i = 0; i < num_samples_per_thread; i++){
//            int val = next_rand(generator) * num_buckets;
//            histogram[val]++;
//        }
//        free_rand(generator);
//    }
    
    
    //Not parallel version
//    rand_gen generator = init_rand();
//    for(int i = 0; i < num_samples; i++){
//        int val = next_rand(generator) * num_buckets;
//        histogram[val]++;
//    }
//    free_rand(generator);
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