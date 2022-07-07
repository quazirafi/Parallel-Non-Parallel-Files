#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define m (4*3)

int main()
{
    omp_set_num_threads(3);
dummyMethod1();
    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < m; i++)
    {
        printf("tid = %d, i = %d\n", omp_get_thread_num(), i);
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