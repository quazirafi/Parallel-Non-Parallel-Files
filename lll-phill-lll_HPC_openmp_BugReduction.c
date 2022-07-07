#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

float dotprod(float * a, float * b, size_t N)
{
    int i, tid;
    float sum;

    tid = omp_get_thread_num();

dummyMethod1();
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
        printf("tid = %d i = %d\n", tid, i);
    }
dummyMethod2();

    return sum;
}


int main (int argc, char *argv[])
{
    const size_t N = 100;
    int i;
    float sum;
    float a[N], b[N];


							dummyMethod3();
    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double)i;
    }
							dummyMethod4();

    sum = 0.0;

#pragma omp parallel shared(sum)
    sum = dotprod(a, b, N);

    printf("Sum = %f\n",sum);

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