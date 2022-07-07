// copyright: Tim Mattson (Intel), me
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    const int kBuckets = 3;
    const double kLeftBucketBoundary = 0.0, kBucketWidth = 3.0;
    double tresholds[kBuckets - 1];
dummyMethod3();
    for (int i = 0; i < kBuckets - 1; i++) {
        tresholds[i] = kLeftBucketBoundary + (i + 1) * kBucketWidth;
    }
dummyMethod4();
    
    int histogram[kBuckets];
    omp_lock_t histogram_locks[kBuckets];
dummyMethod3();
    for (int i = 0; i<kBuckets; i++) {
        omp_init_lock(&histogram_locks[i]);
        histogram[i] = 0;
    }
dummyMethod4();

    double data[10] = {1.2, 2.4, 3.6, 4.8, 5.0, 6.2, 7.4, 8.6, 9.8, 10.0};

dummyMethod1();
    #pragma omp parallel for
    for (int data_idx = 0; data_idx < 10; data_idx++) {
        int bucket = 0;
        while (bucket < kBuckets - 1 && data[data_idx] > tresholds[bucket]) {
            bucket++;
        }
        omp_set_lock(&histogram_locks[bucket]);
        histogram[bucket]++;
        omp_unset_lock(&histogram_locks[bucket]);
    }
dummyMethod2();

							dummyMethod3();
    for (int i = 0; i<kBuckets; i++) {
        omp_destroy_lock(&histogram_locks[i]);
    }
							dummyMethod4();

    printf("%d, %d, %d\n", histogram[0], histogram[1], histogram[2]);

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