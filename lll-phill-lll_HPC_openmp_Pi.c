#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    const size_t N = 100000000;
    double step;

    double pi, sum = 0.;
    int in_circle = 0;

    double x, y;

dummyMethod1();
#pragma omp parallel for reduction(+:in_circle)
    for (int i = 0; i < N; ++i)
    {
        int tid = omp_get_thread_num();
        struct timeval t;
        gettimeofday(&t, NULL);
        unsigned int seed = (t.tv_usec + tid) * 1000;

        x = ((double)rand_r(&seed) / (RAND_MAX));
        y = ((double)rand_r(&seed) / (RAND_MAX));
        if (x*x + y*y < 1 + 1e-15)
        {
            ++in_circle;
        }

    }
dummyMethod2();

    printf("pi = %.16f\n", 4 * (double)in_circle / N);

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