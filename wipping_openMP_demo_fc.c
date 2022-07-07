#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define l 4
#define m 4
#define n 2

int main()
{
    int tid, i, j, k, counter;
    omp_set_num_threads(3);

    counter = 0;
dummyMethod1();
    #pragma omp parallel for collapse(2) private(i, j, k, tid) firstprivate(counter)
    for(i = 1; i <= l; i++) {
        for(j = 1; j <= m; j++) {
            for(k = 1; k <= n; k++){
                tid = omp_get_thread_num();
                counter = counter + 1;
                printf("tid = %d, counter = %d, i = %d, j = %d, k = %d\n", tid, counter, i, j, k);
            }
        }
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