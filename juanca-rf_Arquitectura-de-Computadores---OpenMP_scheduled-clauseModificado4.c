#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#else
#define omp_get_thread_num() 0
#endif

int main(int argc, char **argv){
    int i, n = 200, chunk, a[n], suma = 0, dinamic, nthreads, limit, chunk2;
    omp_sched_t tipo;

    if (argc < 3){
        fprintf(stderr, "\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n > 200) n = 200;
    chunk = atoi(argv[2]);

dummyMethod3();
    for (i = 0; i < n; i++) a[i] = i;

    #pragma omp parallel  for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
dummyMethod4();
							dummyMethod1();
    for (i = 0; i < n; i++)
    {
        if(i==0){ 
            printf("\n DENTRO DE LA REGION PARALLEL\n \tomp_get_num_threads():  %d\n", omp_get_num_threads() );
            printf("\tomp_get_num_procs(): %d\n", omp_get_num_procs() );
            printf("\tomp_in_parallel(): %d\n\n", omp_in_parallel() );
        }  
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
            omp_get_thread_num(), i, a[i], suma);
    }  
							dummyMethod2();

    printf("\nFuera de 'parallel for' suma=%d\n", suma);
    printf("\n FUERA DE LA REGION PARALLEL\n \tomp_get_num_threads():  %d\n", omp_get_num_threads() );
    printf("\tomp_get_num_procs(): %d\n", omp_get_num_procs() );
    printf("\tomp_in_parallel(): %d\n", omp_in_parallel() );
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