#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
int main(int argc, char *argv[]) { /* omp_lastprivate.c  */
int i;
int x = 33;

dummyMethod1();
    #pragma omp parallel for lastprivate(x)
    for(i = 0; i <= 10; i++){
        x = i;
        printf("Número da thread: %d    x: %d\n",omp_get_thread_num(),x);
    }
dummyMethod2();
    printf("x é %d\n", x);
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