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

//Modificado para guardar en orden de iteracion el numero de thread
int main(int argc, char **argv)
{
    int i, n = 20, a[n], orden[n], suma = 0;
    if (argc < 2)
    {
        fprintf(stderr, "\nFalta iteraciones \n");
        exit(-1);
    }
    n = atoi(argv[1]);
    if (n > 20)
        n = 20;
dummyMethod3();
    for (i = 0; i < n; i++)
        a[i] = i;
#pragma omp parallel for num_threads(3) firstprivate(suma) \
dummyMethod4();
dummyMethod1();
    lastprivate(suma) schedule(runtime)
    for (i = 0; i < n; i++)
    {   
        orden[i] = omp_get_thread_num();
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(), i, a[i], suma);
    }
dummyMethod2();

    printf("\n\nOrden de hebras por iteraciones\n");
							dummyMethod3();
    for(i = 0; i < n; i++){
        printf("%d\n",orden[i]);
    }
							dummyMethod4();
    printf("Fuera de 'parallel for' suma=%d\n", suma);
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