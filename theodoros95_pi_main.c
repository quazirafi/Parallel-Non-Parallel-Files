#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2000000000

int main(int argc, char *argv[]) {

    long long int limit = N;

    if (argc == 2) {
        limit *= atoi(argv[1]);
    }

    double sum = 0;

dummyMethod1();
#pragma omp parallel for default(none) shared(limit) reduction(+: sum)
    for (long long int i = 1; i <= limit; ++i) {
        sum += 1 / (1 + pow(((double) i - 0.5) / limit, 2));
    }
dummyMethod2();

    printf("Pi = %f\n", 4 * sum / limit);

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