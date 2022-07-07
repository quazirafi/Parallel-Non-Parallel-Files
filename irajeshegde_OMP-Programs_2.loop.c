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
dummyMethod1();
#pragma omp parallel for
    for (int i = 1; i <= max; i++)
        printf("%d -> %d\n", omp_get_thread_num(), i);
    return 0;
dummyMethod2();
}
/*
Commands:
gcc-10 -fopenmp -o loop 2.loop.c
env OMP_NUM_THREADS=8 ./loop 10

Output:
0 -> 1
0 -> 2
2 -> 5
1 -> 3
1 -> 4
3 -> 6
4 -> 7
5 -> 8
6 -> 9
7 -> 10
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