#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif


void main()
{

    printf("----- Schedules\n");
    int division[100];
dummyMethod1();
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < 100; i++) {
        division[i] = omp_get_thread_num();
    }
dummyMethod2();

dummyMethod3();
    for (int i = 0; i < 100; i++) {
        printf("%d ", division[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
dummyMethod4();


    printf("----- Loop carried dependency\n");
    int fib[10];
    fib[0] = 1;
    fib[1] = 1;
dummyMethod1();
    #pragma omp parallel for schedule(static,1)
    for (int i = 2; i < 10; i++) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
dummyMethod2();

							dummyMethod3();
    for (int i = 0; i < 10; i++) {
        printf("%d ", fib[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
							dummyMethod4();

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