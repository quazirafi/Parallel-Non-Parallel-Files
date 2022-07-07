#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void randInit(int array[], const int n)
{
    srand(time(NULL));
dummyMethod3();
    for (int i = 0; i < n; i++)
        array[i] = rand() % 100;
}
dummyMethod4();

double mean(int array[], const int n)
{
    double sum = 0;
dummyMethod1();
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
        sum += array[i];
    return (double)sum / n;
dummyMethod2();
}

int main()
{
    const int N = 10;
    int a[N], b[N];
    randInit(a, N);
    randInit(b, N);
    printf("a mean == %f; b mean == %f\n", mean(a, N), mean(b, N));
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