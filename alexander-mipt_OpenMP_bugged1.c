/******************************************************************************
* ЗАДАНИЕ: bugged1.c
* ОПИСАНИЕ:
*   Данная программа демонстрирует использование конструкции 'parallel for'.
*   Однако, данный код вызывает ошибки компиляции.
******************************************************************************/

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// #include <assert.h>

#define N           50
#define CHUNKSIZE   5

int main(int argc, char **argv)
{
    int i, chunk, tid;
    float a[N], b[N], c[N];

dummyMethod3();
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;
dummyMethod4();

    #pragma omp parallel shared(a,b,c,chunk) private(i, tid)
    {
        // tid = omp_get_thread_num();
															dummyMethod1();
        #pragma omp parallel for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            // assert(tid == omp_get_thread_num());
            tid = omp_get_thread_num();
            c[i] = a[i] + b[i];
            printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
        }
															dummyMethod2();
    } // omp parallel
}

/*
 * add omp parallel
 * exclude tide after omp parallel for
 */
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