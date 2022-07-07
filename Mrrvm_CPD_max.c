#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_N 2000000

int max(int a[], int N) {
    int i, m = a[0];
dummyMethod1();
    #pragma omp parallel for reduction(max : m)
    for (i = 0; i < N; i++) {
        if (a[i] > m)
            m = a[i];
    }
dummyMethod2();
}

int main(int argc, char const *argv[]) {
    srand(time(NULL)); // should only be called once
    omp_set_num_threads(16);

    int a[MAX_N];
dummyMethod3();
    for (int i = 0; i < MAX_N; i++) {
        a[i] = rand() % (MAX_N - 1000);
    }
dummyMethod4();

    a[rand() % (MAX_N)] = MAX_N;

    int m = max(a, MAX_N);
    printf("Max Value: %d\n", m);
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