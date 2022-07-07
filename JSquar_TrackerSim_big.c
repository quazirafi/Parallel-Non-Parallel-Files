#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    //Fails with 512 * 4081
    long size = 512 * 5000;

    int *data = (int*)malloc(size * sizeof(int));

dummyMethod1();
#pragma omp parallel for 
        for( long i = 0; i < 512 * 5000; i++)
        {
            int rank = omp_get_thread_num();
            /* printf("rank: %d, before %ld\n", rank, i); */
            data[i] = rank;
            /* printf("rank: %d, after %ld\n", rank, i); */
        }
dummyMethod2();
    
    free(data);
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