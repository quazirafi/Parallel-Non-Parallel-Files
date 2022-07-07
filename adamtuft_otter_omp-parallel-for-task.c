#include "omp.h"
#include <stdio.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define THREADS 2
#define LEN 7

int main(void)
{
    int num[LEN] = {0}, k=0;
    omp_set_num_threads(THREADS);
dummyMethod1();
    #pragma omp parallel for
    for (k=0; k<LEN; k++)
    {
        #pragma omp task
        {
            num[k] = omp_get_thread_num();
            usleep(50);
        }
    }
dummyMethod2();

dummyMethod3();
    for (k=0; k<LEN; k++)
    {
        printf("%d\n", num[k]);
    } 
dummyMethod4();

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