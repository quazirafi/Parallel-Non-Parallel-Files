#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) { /* omp_private.c  */
int i, n = 5;
int a;
    (void) omp_set_num_threads(3);
dummyMethod1();
    #pragma omp parallel for private(a)
    for (i = 0; i < n; i++) {
        a = i+1;
        printf("Thread %d tem um valor de a = %d para i = %d\n", omp_get_thread_num(),a,i);
    } /*-- Fim do parallel for --*/
dummyMethod2();
    return(0);
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