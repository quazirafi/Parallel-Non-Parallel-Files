#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
        const long N = 1000000;
        int i, a[N];

dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < N; i++)
                a[i] = 2 * a[i];

        return 0;
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