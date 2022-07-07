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

int main(int argc, char **argv)   {

   int i, n = 7,chunk, a[n],suma=0;

   if(argc < 2)     {
          fprintf(stderr,"\nFalta chunk \n");
          exit(-1);
     }
   chunk = atoi(argv[1]);

dummyMethod3();
   for (i=0; i<n; i++)    a[i] = i;

   #pragma omp parallel for firstprivate(suma) \
dummyMethod4();
dummyMethod1();
                lastprivate(suma) schedule(static,chunk)
                // El schedule organiza la forma de repartir las iteraciones del bucle
                //Con static, establece un Round Robin, y departiendo de n en n, siendo n el chunck
                //Es similar a un reparto de cartas, se reparte por jugador tantas cartas como
                //determine el chunk.
   for (i=0; i<n; i++)
   {   suma = suma + a[i];
dummyMethod2();
       printf(" thread %d suma a[%d] suma=%d \n",
             omp_get_thread_num(),i,suma);
   }

   printf("Fuera de 'parallel for' suma=%d\n",suma);

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