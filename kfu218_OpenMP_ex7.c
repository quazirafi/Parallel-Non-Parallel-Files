#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    const int N = 12;
    int a[N], b[N], c[N];
    srand(time(NULL));
    printf("static schedule\n");
    omp_set_num_threads(3);
dummyMethod1();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 200;
        printf("thread num %d, %d iteration, a[i] = %d, b[i] = %d\n", omp_get_thread_num(), i, a[i], b[i]);
    }
dummyMethod2();

    printf("\ndynamic schedule\n");
    omp_set_num_threads(4);
dummyMethod1();
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
        printf("thread num %d, %d iteration, c[i] = %d\n", omp_get_thread_num(), i, c[i]);
    }
dummyMethod2();
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