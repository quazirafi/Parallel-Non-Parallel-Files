#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int tid, i, j , a[4], b[4];

    omp_set_num_threads(3);
dummyMethod3();
    for(i = 0; i < 4; i++)
    {
        a[i] = -10;
        b[i] = -10;
    }
dummyMethod4();

    tid = omp_get_thread_num();
dummyMethod3();
    for(i = 0; i < 4; i++)
    {
        printf("a[%d] = %d    ", i, a[i]);
    }
dummyMethod4();
    printf("thread %d\n", tid);

dummyMethod3();
    for(j = 0; j < 4; j++)
    {
        printf("b[%d] = %d    ", j, b[j]);
    }
dummyMethod4();
    printf("thread %d\n", tid);

    printf("---------before parallel\n");
    printf("---------during parallel\n");

							dummyMethod1();
    #pragma omp parallel for private(i, j, tid), firstprivate(a, b), lastprivate(b)
    for(i = 0; i < 4; i++)
    {
        tid = omp_get_thread_num();
        printf("a[%d] = %d, b[%d] = %d, thread_%d\n", i, a[i], i, b[i], tid);
        a[i] = (i+1)*3 + tid;
        b[i] = (i+1)*7 + tid;
        printf("a[%d] = %d, b[%d] = %d, thread_%d change\n", i, a[i], i, b[i], tid);
    }
							dummyMethod2();
    printf("\n");
    tid = omp_get_thread_num();
    printf("---------after parallel\n");
							dummyMethod3();
    for(i = 0; i < 4; i++)
    {
        printf("a[%d] = %d    ", i, a[i]);
    }
							dummyMethod4();
    printf("thread %d\n", tid);
							dummyMethod3();
    for(j = 0; j < 4; j++)
    {
        printf("b[%d] = %d    ", j, b[j]);
    }
							dummyMethod4();
    printf("thread %d\n", tid);
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