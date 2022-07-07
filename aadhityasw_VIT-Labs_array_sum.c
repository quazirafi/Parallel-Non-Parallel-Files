#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int sum = 0;
dummyMethod1();
    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<5;i++)
    {
        sum += a[i];
        printf("sum = %d\ti = %d\tthreadno = %d\n", sum, i, omp_get_thread_num());
    }
dummyMethod2();
    printf("sum = %d\n", sum);
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