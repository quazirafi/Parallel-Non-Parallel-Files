#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define m 5

int main()
{
    int tid, i;
    omp_lock_t lock;

    omp_set_num_threads(3);
    omp_init_lock(&lock);
    
dummyMethod1();
    #pragma omp parallel for private(tid, i) shared(lock)
    for(i = 0; i < m; i++)
    {
        tid = omp_get_thread_num();
        omp_set_lock(&lock);
        printf("thread_id = %d, i = %d\n", tid, i);
        omp_unset_lock(&lock);
    }
dummyMethod2();

    omp_destroy_lock(&lock);
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