#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static omp_lock_t lock;

int main(int argc, char const *argv[])
{
    /* code */
    omp_init_lock(&lock);

dummyMethod1();
    #pragma omp parallel for
    for (size_t i = 0; i < 5; i++)
    {
        omp_set_lock(&lock);
        printf("%d+\n", omp_get_thread_num());
        printf("%d-\n", omp_get_thread_num());
        omp_unset_lock(&lock);
    }
dummyMethod2();

    // always use a ref in lock operations
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