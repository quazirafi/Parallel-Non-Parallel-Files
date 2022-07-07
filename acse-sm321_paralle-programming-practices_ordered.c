#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void work(int k)
{
    #pragma omp ordered
    printf("%d\n",k);
    // a ordered function can only be executed by ordered region
}

void foo1(int lb, int ub, int stride)
{
    int i;
dummyMethod1();
    #pragma omp parallel for ordered schedule(dynamic)
    for (i = lb; i <= ub; i+=stride)
    {
        work(i);
    }
dummyMethod2();
    
}

int main(int argc, char const *argv[])
{
    foo1(0,100,5);
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