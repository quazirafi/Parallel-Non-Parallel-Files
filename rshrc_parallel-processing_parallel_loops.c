#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
    int arr[50000], count0 = 0, count1 = 0, count2 = 0, count3 = 0;
dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < 50000; i++)
    {
        int thread_being_used = omp_get_thread_num();
        arr[i] = 5 * i;
        printf("Using Thread : %d\n", thread_being_used);
        if (thread_being_used == 0)
            count0++;
        else if (thread_being_used == 1)
            count1++;
        else if (thread_being_used == 2)
            count2++;
        else
            count3++;
    }
dummyMethod2();
    printf("Thread 0 is used : %d\n", count0);
    printf("Thread 1 is used : %d\n", count1);
    printf("Thread 2 is used : %d\n", count2);
    printf("Thread 3 is used : %d\n", count3);
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