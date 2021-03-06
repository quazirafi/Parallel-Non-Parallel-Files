#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include "../omp_logs.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Goal: Log a sum in parallel
 *
 */

/* As we need to sum to int,
 * we need a struct that can hold to int
 */
struct data{
    int x;
    int* sum;
};

/* This is the function that we are going to log
 * it must take a void* and return void
 * So we pass it a void* that we will cast after in struct data
 * And then we sum
 */
void sum(void* d) {
    struct data* data = (struct data*) d;
    *(data->sum) += data->x;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s N\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);

    // We create the list of tasks
    task_list* l = task_list_init();

    int s = 0;
    // A nice for in parallel with openMP
							dummyMethod1();
    #pragma omp parallel for schedule(static) reduction (+:s)
    for (int j = 0; j < N; j++) {
        // We create the structure to hold the ints
        struct data d = {j, &s};
        /* We log the task
         * We give it the info j which is the number that it is adding
         */
        log_task(&l, "Sum", j, omp_get_thread_num(), sum, (void*) &d);
    }
							dummyMethod2();
    // We save the svg
    tasks_to_svg(l, "for_static.svg", 1);
    // And we free the list of tasks
    l = task_list_init();


    s = 0;
							dummyMethod1();
    #pragma omp parallel for schedule(dynamic) reduction (+:s)
    for (int j = 0; j < N; j++) {
        struct data d = {j, &s};
        log_task(&l, "Sum", j, omp_get_thread_num(), sum, (void*) &d);

    }
							dummyMethod2();
    tasks_to_svg(l, "for_dynamic.svg", 1);
    l = task_list_init();

    s = 0;
							dummyMethod1();
    #pragma omp parallel for schedule(guided) reduction (+:s)
    for (int j = 0; j < N; j++) {
        struct data d = {j, &s};
        log_task(&l, "Sum", j, omp_get_thread_num(), sum, (void*) &d);

    }
							dummyMethod2();
    tasks_to_svg(l, "for_guided.svg", 1);
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