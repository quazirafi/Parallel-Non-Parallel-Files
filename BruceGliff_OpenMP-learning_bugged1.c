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

															dummyMethod1();
    #pragma omp parallel for    \
        shared(a, b, c, chunk)  \
        private(i, tid)         \
        schedule(static, chunk)
    //{
        //tid = omp_get_thread_num(); <- right after parallel for has to be a loop.
        for (i = 0; i < N; i++)
        {
            tid = omp_get_thread_num(); // <- new pos
            c[i] = a[i] + b[i];
            printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
        }
															dummyMethod2();
    //}
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