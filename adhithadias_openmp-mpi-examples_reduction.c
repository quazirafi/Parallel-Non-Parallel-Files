#include <stdio.h>
#include "omp.h"
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000000
#define NUM_THREADS 4

void initialze_array(const int n, float *a, const float value);
void print_array(const int n, const float *a);

void initialze_array(const int n, float *a, const float value) {
dummyMethod3();
    for (int i = 0; i < n; i++ ) {
      a[ i ] = value; 
   }
dummyMethod4();
}

void print_array(const int n, const float *a) {
    printf("[");
dummyMethod3();
    for (int i=0; i<10; i++){
        printf("%f ", a[i]);
    }
dummyMethod4();
    printf("]\n");
}

void print_thread_info(int i) {
    int curr_thread, nthread;
    int len = 20;
    char name[20];
    curr_thread = omp_get_thread_num();
    nthread = omp_get_num_threads();
    gethostname(name, len);
    printf("name: %s, thread_count: %d, current_thread: %d, i: %d\n", name, nthread, curr_thread, i);
    return;
}

/*  Example to check master construct and single construct directives
*   single and master constructs when specified, the statement is executed by only one thread
*   single construct, unless otherwise specified with nowait clause, wait at an implicit barrier
*   at the end of the single construct
*/
void reduction() {

    printf("Starting the reduction script\n");
    clock_t start, end;
    double start_t, end_t;

    printf("\n==============INITIALITING THE ARRAY=================\n");
    float *x = (float *) malloc(N*sizeof(float));
    initialze_array(N, x, 1.0);
    float y = 0.0;

    printf("\n==============PART 1: SEQUENTIAL EXECUTION=================\n");
    start = clock();
    start_t = omp_get_wtime(); 
							dummyMethod3();
    for(int i=0; i<N; i++) {
        y += x[i];
    }
							dummyMethod4();
    end_t = omp_get_wtime(); 
    end = clock();
    printf("Work took %f seconds\n", end_t-start_t);
    printf("Answer: %f, s_t: %ld, e_t: %ld, time taken for serial reduction: %f\n", y, start, end, (end-start)/(double)CLOCKS_PER_SEC);

    printf("\n==============PART 2: PARALLEL EXECUTION=================\n");
    omp_set_num_threads(NUM_THREADS);

    y = 0.0;

    int nthreads = omp_get_num_threads();
    float res[NUM_THREADS*8];
    initialze_array(NUM_THREADS*8, res, 0.0);
    int i=0;
    
    start = clock();
    start_t = omp_get_wtime(); 
							dummyMethod1();
    #pragma omp parallel for
    for (i=0; i < N; i++) {
        res[omp_get_thread_num()*8] += x[i];
    }
							dummyMethod2();
							dummyMethod3();
    for (i=0; i<8*NUM_THREADS; i+=NUM_THREADS) {
        y += res[i];
    }
							dummyMethod4();
    end_t = omp_get_wtime(); 
    end = clock();

    printf("Work took %f seconds\n", end_t-start_t);
    printf("Answer: %f, s_t: %ld, e_t: %ld, time taken for serial reduction: %f\n", y, start, end, (end-start)/(double)CLOCKS_PER_SEC);

    y = 0.0;
    float t[NUM_THREADS] = {0., 0., 0., 0.};
    start = clock();
    start_t = omp_get_wtime(); 
							dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i<N; i++) {
        t[omp_get_thread_num()] += x[i];
        // printf("num: %f \n", x[i]);
        // print_thread_info(i);
    }
							dummyMethod2();
							dummyMethod3();
    for (int i=0; i<4; i++) {
        y += t[i];
    }
							dummyMethod4();
    end_t = omp_get_wtime(); 
    end = clock();
    print_array(4, t);


    printf("Work took %f seconds\n", end_t-start_t);
    printf("Answer: %f, s_t: %ld, e_t: %ld, time taken for serial reduction: %f\n", y, start, end, (end-start)/(double)CLOCKS_PER_SEC);



    printf("\n==============PART 3: OpenMP REDUCTION=================\n");
    y = 0.0;

    start = clock();
    start_t = omp_get_wtime(); 
							dummyMethod1();
    #pragma omp parallel for shared(x) reduction(+:y)
    for (int i=0; i<N; i++) {
        y += x[i];
    }
							dummyMethod2();
    end_t = omp_get_wtime(); 
    end = clock();
    printf("Work took %f seconds\n", end_t-start_t);
    printf("Answer: %f, s_t: %ld, e_t: %ld, time taken for serial reduction: %f\n", y, start, end, (end-start)/(double)CLOCKS_PER_SEC);

    free(x);
    return;

}

int main (int argc, char *argv []) {

    reduction();
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