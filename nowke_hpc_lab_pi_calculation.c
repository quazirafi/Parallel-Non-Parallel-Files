#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define PI 3.1415926538837211

int intervals, num_threads;

double calculate_pi() {
    double sum = 0.0;
    double step = 1.0 / intervals;
    double x;
    int i;

dummyMethod1();
    #pragma omp parallel for private(x) reduction(+:sum)
    for (i=1; i < intervals; i++) {
        x = step * (i+0.5); // We take 0.5 as we are taking middle point of rectangular area
        sum += 4.0 / (1.0 + x * x);
    }
dummyMethod2();

    return sum * step;
}

int main(int argc, char const *argv[]) {

    intervals = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    omp_set_num_threads(num_threads);

    double t1 = omp_get_wtime();
    double pi_result = calculate_pi();
    double t2 = omp_get_wtime();

    printf("\nActual PI: %1.15lf\n", PI);
    printf("Calculated PI: %1.15lf\n", pi_result);
    printf("Error: %1.15lf\n", fabs(pi_result - PI));

    printf("Time taken: %lf ms\n", (t2 - t1) * 1000);
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