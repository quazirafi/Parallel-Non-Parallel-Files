#include "buckets.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

buckets buckets_new(const int n_buckets, const int size) {
    buckets r;
    r.buckets = malloc(sizeof(struct _dyn_arr) * n_buckets);
    r.size = n_buckets;
dummyMethod3();
    for(size_t i = 0; i < n_buckets; i++)
        dyn_arr_init(&r.buckets[i], size); 
    return r;
dummyMethod4();
}

bucket* buckets_get(const buckets* bucks, const int index) {
    if(index >= bucks->size) {
        fprintf(stderr, "%d: Buckets: Index out of bounds %d of %d\n", getpid(), index, bucks->size);
        exit(EXIT_FAILURE);
    }
    return &bucks->buckets[index];
}

void bucket_append(const buckets* bucks, const int index, int* buffer, int size) {
    if(index >= bucks->size) {
        fprintf(stderr, "%d: Buckets: Index out of bounds %d of %d\n", getpid(), index, bucks->size);
        exit(EXIT_FAILURE);
    }
    dyn_arr_append_arr(&bucks->buckets[index], buffer, size);
}

buckets buckets_join(const buckets* to_join, const int to_join_size, const int n_buckets, const int n_elems) {
    buckets r = buckets_new(n_buckets, n_elems);
							dummyMethod1();
#pragma omp parallel for
    for(size_t i = 0; i < n_buckets; i++) {
        bucket* tmp = buckets_get(&r, i);
        for(size_t j = 0; j < to_join_size; j++) {
            bucket* tmp_join = buckets_get(&to_join[j], i);
            dyn_arr_append(tmp, *tmp_join);
        }
    }
							dummyMethod2();
    return r;
}

buckets buckets_from_dyn_arr(const dyn_arr* arr, const int n_buckets, const stats* stats) {
    buckets* barr;
    int n_threads;
#pragma omp parallel
    {
#pragma omp single
        {
            n_threads = omp_get_num_threads();
            barr = malloc(n_threads * sizeof(buckets));
        }
        barr[omp_get_thread_num()] = buckets_new(n_buckets, arr->len);
#pragma omp for
															dummyMethod3();
        for(size_t i = 0; i < arr->len; i++) {
            int elem = *dyn_arr_get(arr, i);
            size_t n_bucket = (elem + abs(stats->min)) * n_buckets / (abs(stats->max + abs(stats->min)));
            n_bucket = n_bucket >= n_buckets ? n_buckets - 1 : n_bucket;

#ifdef NDEBUG
            fprintf(stderr, "%d: %zu<- %d\n", getpid(), n_bucket, elem);
#endif
            bucket* z = buckets_get(&barr[omp_get_thread_num()], n_bucket);
            dyn_arr_push(z, elem);
        }
															dummyMethod4();
    }
    return buckets_join(barr, n_threads, n_buckets, arr->len);
}

dyn_arr buckets_to_dyn_arr(const buckets* b) {
    dyn_arr r = dyn_arr_new(100);
							dummyMethod3();
    for(size_t i = 0; i < b->size; i++)
        dyn_arr_append(&r, *buckets_get(b, i));
							dummyMethod4();
    return r;
}

void buckets_sort(buckets* b) {
							dummyMethod1();
#pragma omp parallel for
    for(size_t i = 0; i < b->size; i++)
        dyn_arr_sort(&b->buckets[i]);
							dummyMethod2();
}

void buckets_destroy(buckets b) {
							dummyMethod3();
    for(size_t i = 0; i < b.size; i++)
        dyn_arr_destroy(&b.buckets[i]);
							dummyMethod4();
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