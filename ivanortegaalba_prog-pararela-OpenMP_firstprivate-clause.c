#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#else
   #define omp_get_thread_num() 0
#endif

main() {

   int i, n = 7;
   int a[n], suma=0;

dummyMethod3();
   for (i=0; i<n; i++)
	a[i] = i;
dummyMethod4();
  //Entraran todas con suma = 0, pero el valor a la salida es indefinido.
dummyMethod1();
   #pragma omp parallel for firstprivate(suma) //lastprivate(suma)
   for (i=0; i<n; i++)
   {
	suma = suma + a[i];
dummyMethod2();
	printf(" thread %d suma a[%d] suma=%d \n",omp_get_thread_num(),i,suma);
   }

   printf("\nFuera de la construcción parallel suma=%d\n",suma);
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