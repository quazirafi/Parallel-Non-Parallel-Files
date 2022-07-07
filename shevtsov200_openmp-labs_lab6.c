#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdbool.h>

#include<time.h>

#include<stdio.h>

#define REQURIED_NUMBER_OF_THREADS 4

int A[15];

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

dummyMethod3();
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
dummyMethod4();

    return true;
}

int countInParallel(int *natural_numbers, int n) {
    if (omp_get_max_threads() < REQURIED_NUMBER_OF_THREADS) {
        printf("not enough threads");
        getch();

        return (0);
    } else {
        omp_set_num_threads(REQURIED_NUMBER_OF_THREADS);
    }

    int i;
    int natural_number = 0;

    double intermidiate_sum = 0.0;
    double sum = 0.0;

							dummyMethod1();
    #pragma omp parallel for schedule(static, 5) private(i, natural_number, intermidiate_sum)\
    shared(natural_numbers) reduction(+: sum)
    for (i = 0; i < n; ++i) {
        natural_number = natural_numbers[i];
        if (isPrime(natural_number)) {
            sum = sum + natural_number;

            intermidiate_sum = sum;
            printf("intermediate sum for i=%d = %f\n", i, intermidiate_sum);
        }
    }
							dummyMethod2();

    return sum;
}

int main() {
    int n = sizeof(A) / sizeof(A[0]);

    int i;
    double sum = 0.0;

							dummyMethod1();
    #pragma omp parallel for shared(A)
    for (i = 0; i < n; ++i) {
        A[i] = 2;
    }
							dummyMethod2();

    sum = countInParallel(A, n);

    printf("sum = %f\n", sum);

    return (0);
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