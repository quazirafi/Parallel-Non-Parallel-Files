#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int nthreads, tid, i;
    omp_set_num_threads(2);

    printf("for schedule(static)\n");
dummyMethod1();
    #pragma omp parallel for private(i) schedule(static)
    for(i = 0; i < 10; i++)
    {
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("nthreads = %d, id = %d, i = %d\n", nthreads, tid, i);
    }
dummyMethod2();
    printf("\n");

    printf("fpr schedule(static, 2)\n");
dummyMethod1();
    #pragma omp parallel for private(i) schedule(static, 2)
    for(i = 0; i < 10; i++)
    {
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("nthreads = %d, id = %d, i = %d\n", nthreads, tid, i);
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