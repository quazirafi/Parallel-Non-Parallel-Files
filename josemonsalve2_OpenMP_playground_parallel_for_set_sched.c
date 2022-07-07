#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    // Guided
    printf("Guided schedule\n");
    omp_set_schedule(omp_sched_guided, 3);
dummyMethod1();
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < 6; i++) {
        printf("Hi from %d iteration %d \n", omp_get_thread_num(), i);
    }
dummyMethod2();
    // Static
    printf("Static schedule\n");
    omp_set_schedule(omp_sched_static, 3);
dummyMethod1();
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < 6; i++) {
        printf("Hi from %d iteration %d \n", omp_get_thread_num(), i);
    }
dummyMethod2();
    // Dynamic
    printf("Dynamic schedule\n");
    omp_set_schedule(omp_sched_dynamic, 3);
dummyMethod1();
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < 6; i++) {
        printf("Hi from %d iteration %d \n", omp_get_thread_num(), i);
    }
dummyMethod2();
    // Auto
    printf("Auto schedule\n");
    omp_set_schedule(omp_sched_auto, 3);
dummyMethod1();
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < 6; i++) {
        printf("Hi from %d iteration %d \n", omp_get_thread_num(), i);
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