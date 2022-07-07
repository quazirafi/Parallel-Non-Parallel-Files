#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char ** argv)
{
dummyMethod1();
#pragma omp parallel for
    for(unsigned int i = 0; i < 10; ++i)
    {
        unsigned int thread = omp_get_thread_num();
        printf("Thread %d is doing iteration %d.\n", thread, i);
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