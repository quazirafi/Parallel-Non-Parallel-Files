#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int nthreads, tid, i, j;
    int a[3][3], b[3][3], c[3][3];
    omp_set_num_threads(3);
    printf("nthreads   tid   i   j   c[i][j]\n");

dummyMethod1();
    #pragma omp parallel for private(i, j, tid, nthreads) shared(a, b, c)
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            a[i][j] = (i+1) + (j+1);
            b[i][j] = (i+j+2) * 10;
            c[i][j] = a[i][j] + b[i][j];
            tid = omp_get_thread_num();
            nthreads = omp_get_num_threads();
            printf("   %d        %d    %d   %d     %d\n", nthreads, tid, i, j, c[i][j]);
        }
        printf("--------------------------------\n");
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