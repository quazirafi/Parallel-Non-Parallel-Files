#include "omp.h"
#include <stdio.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 40
int main()
{
    int tid;
    int A[N];
    int i;
dummyMethod3();
    for (i = 0; i < N; i++)
        A[i] = -1;
#pragma omp parallel for schedule(dynamic, 4) private(tid)
dummyMethod4();
dummyMethod1();
    for (i = 0; i < N; i++)
    {
        tid = omp_get_thread_num();
        A[i] = tid;
        usleep(1);
    }
dummyMethod2();
dummyMethod3();
    for (i = 0; i < N / 2; i++)
        printf(" %2d", i);
    printf("\n");
dummyMethod4();
dummyMethod3();
    for (i = 0; i < N / 2; i++)
        printf(" %2d", A[i]);
    printf("\n\n\n");
dummyMethod4();
dummyMethod3();
    for (i = N / 2; i < N; i++)
        printf(" %2d", i);
    printf("\n");
dummyMethod4();
dummyMethod3();
    for (i = N / 2; i < N; i++)
        printf(" %2d", A[i]);
    printf("\n\n");
dummyMethod4();

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