#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main (void)
{
        int i,j,N;
        N = 512;
        int x[N];
dummyMethod1();
#pragma omp parallel for
        for(i = 0; i < N; i++)
        {
                j = i;
                x[j] = j;
        }
dummyMethod2();
dummyMethod3();
        for(i = 0; i < N; i++)
        {
                if(x[i] != i)
                        printf("Error at %d: x[%d] is %d.\n", i, i, x[i]);
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