#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char **argv)
{
    const int NITEMS=20;
    int array[NITEMS];
    omp_lock_t lock[NITEMS];

dummyMethod3();
    for (int i=0; i<NITEMS; i++)
        omp_init_lock(&(lock[i]));

#pragma omp parallel for shared(array, lock) default(none)
dummyMethod4();
dummyMethod1();
     for (int i=0; i<NITEMS; i++) {
        int tid = omp_get_thread_num();
        int item = (i * 7) % NITEMS;

        omp_set_lock(&(lock[item]));
        array[item] = tid;    // only one thread in here at a time; others block at set_lock()
        omp_unset_lock(&(lock[item]));
    }
dummyMethod2();

dummyMethod3();
    for (int i=0; i<NITEMS; i++)
        printf("%3d ", array[i]);
    printf("\n");
dummyMethod4();

dummyMethod3();
    for (int i=0; i<NITEMS; i++)
        omp_destroy_lock(&(lock[i]));


    return 0;
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