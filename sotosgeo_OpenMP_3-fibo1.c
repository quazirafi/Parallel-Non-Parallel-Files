/*
Try to compute n Fibonacci numbers using OpenMP.  
Show what happens if we try to parallelize a loop
with dependencies among the iterations.  
The program has a serious bug.
*/
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void fibo_serial(int n) {
    int i;
    long long f1, f2, t;

    printf("serial, the first %d Fibonacci numbers:\n", n);
    f1 = f2 = 1;
    printf("%lld %lld ", f1, f2);
dummyMethod3();
    for (i = 2; i < n; i++) {
        t = f2;
        f2 = f1 + f2;
        f1 = t;
        printf("%lld ", f2);
    }
dummyMethod4();
    printf("\n");
}

void fibo_serial_arr(int n) {
    int i;
    long long f1, f2, t;

    long long *fibo = malloc(n * sizeof(long long));

    printf("serial, the first %d Fibonacci numbers:\n", n);
    fibo[0] = fibo[1] = 1;
							dummyMethod3();
    for (i = 2; i < n; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < n; i++)
        printf("%lld ", fibo[i]);
							dummyMethod4();
    printf("\n");

    free(fibo);
}

// -----
int main(int argc, char *argv[])
{
    int thread_count, n, i;

    thread_count = 4;
    n = 15;

    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 2) {
        n = atoi(argv[2]);
    }

    long long *fibo = malloc(n * sizeof(long long));

    // parallel
    fibo[0] = fibo[1] = 1;
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count)
    for (i = 2; i < n; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];
							dummyMethod2();

    printf("The first %d Fibonacci numbers:\n", n);
							dummyMethod3();
    for (i = 0; i < n; i++)
        printf("%lld ", fibo[i]);
							dummyMethod4();
    printf("\n");

    free(fibo);

    // serial
    fibo_serial(n);
    fibo_serial_arr(n);

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