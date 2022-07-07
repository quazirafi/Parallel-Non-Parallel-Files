#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "sgtime.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define POLY 7

char website[] = "https://github.com/hpcgarage/spatter/wiki/Related-Benchmarks#randomaccess-aka-gups";

int main (int argc, char **argv)
{
    int    gups_n  = 0;  // GUPs n
    int    threads = 0;  // number of omp threads
    size_t size    = 0;  // size of mem in bytes
    size_t len     = 0;  // Len of mem in size_t elems
    size_t updates = 0;  // Number of accesses to mem
    double time    = 0.;
    size_t *mem    = NULL;

    if (argc < 2) {
        printf("Usage: %s <n>\n", argv[0]);
        printf("Choose n as prescribed here: %s\n", website);
        exit(1);
    }

    // Parse input
    sscanf(argv[1], "%d", &gups_n);
    len     = 2 << (gups_n);
    size    = 2 << (gups_n+3);
    updates = 2 << (gups_n+2);
    threads = omp_get_max_threads();

    // Print header
    printf("==============================================\n");
    printf("Welcome to Patrick Lavin's GUPS Implementation\n");
    printf("==============================================\n\n");
    printf("Run Info:\n");
    printf("  n       : %d\n", gups_n);
    printf("  len     : %zu elements\n", len);
    printf("  size    : %zu MiB\n", size>>20);
    printf("  updates : %zu\n", updates);
    printf("  threads : %d\n\n", threads);

    // Allocate memory
    printf("Allocating memory...   ");
    sg_zero_time();
    mem = (size_t*) malloc(size);
    time = sg_get_time_ms();
    printf("Done. (%.2lfms)\n", time);

    // Initialize mem
    printf("Initializing memory... ");
    sg_zero_time();
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < len; i++) {
        mem[i] = i;
    }
							dummyMethod2();
    time = sg_get_time_ms();
    printf("Done. (%.2lfms)\n", time);

    // Initializing RNG
    printf("Initializing RNG...    "); fflush(stdout);
    sg_zero_time();
    size_t random_start[threads];
    random_start[0] = 1;

    size_t accum = 1;
							dummyMethod3();
    for (int i = 1; i < threads; i++) {
        for (int j = 0; j < updates/threads; j++) {
            accum = (accum << 1) ^ (((ssize_t) accum < 0) ? POLY : 0);
        }
        random_start[i] = accum;
    }
							dummyMethod4();
    time = sg_get_time_ms();
    printf("Done. (%.2lfms)\n", time);

    // Run GUPS
    printf("Running GUPS...        "); fflush(stdout);
    sg_zero_time();
    #pragma omp parallel
    {
        size_t random = random_start[omp_get_thread_num()];
        size_t addr = 0;
        #pragma omp for
															dummyMethod3();
        for (int i = 0; i < updates; i++) {
            random = (random << 1) ^ (((ssize_t) random < 0) ? POLY : 0);
            addr   = random >> (64-gups_n);
            mem[addr] = mem[addr] ^ random;
        }
															dummyMethod4();
    }
    time = sg_get_time_ms();
    printf("Done. (%.2lfms)\n\n", time);

    // Report FOMs
    double seconds = time / 1000;
    printf("FOM:       %lf GUPS\n",   updates / (seconds) / 1e9);
    printf("Bandwidth: %lf MB/s\n\n", 8. * 2 * updates / 1000 / 1000 / seconds);

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