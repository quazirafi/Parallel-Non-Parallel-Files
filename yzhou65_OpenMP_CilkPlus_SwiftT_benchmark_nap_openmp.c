#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[]) {
    int n = 100000;
    if(argc > 1) {
        n = atoi(argv[1]);
    }
    int threads = 2;
    if(argc > 2) {
        threads = atoi(argv[2]);
    }

    double start;
    double time;

    start = omp_get_wtime();

    
dummyMethod1();
    #pragma omp parallel for num_threads(threads)
    for(int i = 0; i < n; i++)
    {
        sleep(0);
    }
dummyMethod2();

    time = omp_get_wtime() - start;
    printf("time: %f, task: %d, throughput: %f\n", time, n, n/time);
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