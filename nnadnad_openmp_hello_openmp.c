#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char *argv[]) {
    int nthreads = atoi(argv[1]), t_id;
    int i;
dummyMethod1();
    #pragma omp parallel for private(t_id) 
        for (i = 0; i < 10; i++) {
            t_id = omp_get_thread_num(); // get thread if for each thread
            printf("i : %d, by the way i'm thread %d\n", i, t_id);
        }
dummyMethod2();

        // printf("Hello from thead number %d of %d\n", t_id, nthreads);




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