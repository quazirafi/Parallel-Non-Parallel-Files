#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
    int max;
    sscanf(argv[1], "%d", &max);
    //making two for loops parallel
dummyMethod1();
#pragma omp parallel for collapse(2)
    for (int i = 1; i <= max; i++)
        for (int j = 1; j <= max; j++)
            printf("%d -> (%d, %d)\n", omp_get_thread_num(), i, j);
    return 0;
dummyMethod2();
}
/*
Commands:
gcc-10 -fopenmp -o nested 3.nestedfor.c
env OMP_NUM_THREADS=8 ./nested 10

Output:
*/
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