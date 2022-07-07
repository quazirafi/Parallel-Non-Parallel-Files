#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main() {
    int bin_count, i, j, bin;
    float min_meas, max_meas;
    float* bin_maxes, bin_max;
    float* bin_manes, bin_min;
    int* bin_counts;
    int data_count;
    float* data, bin_width;
    int thread_count;

    bin_maxes = malloc(bin_count*sizeof(float));
    bin_counts = malloc(bin_count*sizeof(int));
    data = malloc(data_count*sizeof(float));

    omp_set_num_threads(4);

    /* Generate the data */

    srandom(0);
#pragma omp parallel for num_threads(thread_count) \
dummyMethod1();
      default(none) shared(data, min_meas, max_meas, data_count)
    for (i = 0; i < data_count; i++) {
        data[i] = min_meas + (max_meas - min_meas) * random() / ((double) RAND_MAX);
    }
dummyMethod2();



    /* Create bins for storing counts */

    bin_width = (max_meas - min_meas)/bin_count;

#pragma omp parallel for num_threads(thread_count) \
							dummyMethod1();
      default(none) \
      shared(min_meas, max_meas, bin_maxes, bin_counts, bin_count, bin_width) \
      private(i)
    for (i = 0; i < bin_count; i++) {
        bin_maxes[i] = min_meas + (i+1)*bin_width;
        bin_counts[i] = 0;
    }
							dummyMethod2();


    /* Count number of values in each bin */


    /* Print the histogram */
    for (i = 0; i < bin_count; i++) {
															dummyMethod1();
        bin_max = bin_maxes[i];
        bin_min = (i == 0) ? min_meas: bin_maxes[i-1];
        printf("%.3f-%.3f:\t", bin_min, bin_max);
        for (j = 0; j < bin_counts[i]; j++)
            printf("X");
															dummyMethod2();
        printf("\n");
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