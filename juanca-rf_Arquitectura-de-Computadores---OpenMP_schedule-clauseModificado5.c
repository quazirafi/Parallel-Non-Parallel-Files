#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int i, modifier, n = 7, chunk, a[n], suma = 0;
    omp_sched_t kind;
    char ckind[20];

    if (argc < 2){ fprintf(stderr, "\nFalta el tamaÃ±o de chunk\n");exit(-1);}
    chunk = atoi(argv[1]);

dummyMethod3();
    for (i = 0; i < n; i++) a[i] = i;

    #pragma omp parallel for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
dummyMethod4();
															dummyMethod1();
        for (i = 0; i < n; i++){
            if (i == 0){ //Antes de cambiar la variables
                printf("\n_______________________________________________________________\n");
                printf("\nAntes del cambio DENTRO PARALLEL:");
                printf("\n\tdyn-var: %d", omp_get_dynamic());
                printf("\n\tnthreads-var: %d", omp_get_max_threads());
                omp_get_schedule(&kind, &modifier);
                switch (kind){
                case omp_sched_dynamic:
                    strcpy(ckind, "dinamico");
                    break;
                case omp_sched_static:
                    strcpy(ckind, "estatico");
                    break;
                case omp_sched_guided:
                    strcpy(ckind, "guided");
                    break;
                case omp_sched_auto:
                    strcpy(ckind, "auto");
                    break;
                }
                printf("\n\trun-sched-var: %s\n", ckind);
                //Despues de cambiar las variables
                omp_set_dynamic(1);
                omp_set_num_threads(4);
                kind = omp_sched_static;
                omp_set_schedule(kind, modifier);
                printf("\n_______________________________________________________________\n");
                printf("\nDESPUES del cambio DENTRO PARALLEL:");
                printf("\n\tdyn-var: %d", omp_get_dynamic());
                printf("\n\tnthreads-var: %d", omp_get_max_threads());
                omp_get_schedule(&kind, &modifier);
                switch (kind)
                {
                case omp_sched_dynamic:
                    strcpy(ckind, "dinamico");
                    break;
                case omp_sched_static:
                    strcpy(ckind, "estatico");
                    break;
                case omp_sched_guided:
                    strcpy(ckind, "guided");
                    break;
                case omp_sched_auto:
                    strcpy(ckind, "auto");
                    break;
                }
                printf("\n\trun-sched-var: %s\n", ckind);
                printf("\n_______________________________________________________________\n");
            }

            suma = suma + a[i];
            printf(" thread %d suma a[%d] suma=%d \n", omp_get_thread_num(), i, suma);
        }
															dummyMethod2();
    printf("Fuera de 'parallel for' suma=%d\n", suma);
    //Antes de cambiar la variables
    printf("\n_______________________________________________________________\n");
    printf("\nAntes del cambio FUERA PARALLEL:");
    printf("\n\tdyn-var: %d", omp_get_dynamic());
    printf("\n\tnthreads-var: %d", omp_get_max_threads());
    omp_get_schedule(&kind, &modifier);
    switch (kind){
    case omp_sched_dynamic:
        strcpy(ckind, "dinamico");
        break;
    case omp_sched_static:
        strcpy(ckind, "estatico");
        break;
    case omp_sched_guided:
        strcpy(ckind, "guided");
        break;
    case omp_sched_auto:
        strcpy(ckind, "auto");
        break;
    }
    printf("\n\trun-sched-var: %s\n", ckind);

    //Despues de cambiar las variables
    omp_set_dynamic(1);
    omp_set_num_threads(4);
    kind = omp_sched_static;
    omp_set_schedule(kind, modifier);
    printf("\n_______________________________________________________________\n");
    printf("\nDESPUES del cambio FUERA PARALLEL:");
    printf("\n\tdyn-var: %d", omp_get_dynamic());
    printf("\n\tnthreads-var: %d", omp_get_max_threads());
    omp_get_schedule(&kind, &modifier);
    switch (kind){
    case omp_sched_dynamic:
        strcpy(ckind, "dinamico");
        break;
    case omp_sched_static:
        strcpy(ckind, "estatico");
        break;
    case omp_sched_guided:
        strcpy(ckind, "guided");
        break;
    case omp_sched_auto:
        strcpy(ckind, "auto");
        break;
    }
    printf("\n\trun-sched-var: %s\n", ckind);
    printf("\n_______________________________________________________________\n");

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