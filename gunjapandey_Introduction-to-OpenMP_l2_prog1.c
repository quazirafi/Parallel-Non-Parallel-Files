#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int a[10], b[10], i, sum[10];
dummyMethod3();
    for(i=0; i<10; i++)
    {
        printf("Enter values: ");
        scanf("%d%d", &a[i], &b[i]); 
    }
dummyMethod4();
    
dummyMethod1();
    #pragma omp parallel for
    for (i=0; i<10; i++)
    {
        sum[i] = a[i] + b[i];
        printf("CPU: %d\tThread: %d\tValue: %d\n", sched_getcpu(), omp_get_thread_num(), sum[i]);
    }
dummyMethod2();
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