#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
   int a=5, j;
   omp_set_num_threads(4);            // uso 4 thread nella regione parallela 
dummyMethod1();
   #pragma omp parallel for lastprivate(a)  // regione for parallela
   for (j=0; j<7;j++)                 //      
     {
        if (omp_get_thread_num()== 0)sleep(2); // rallento il thread  0
   a = j + 2;
dummyMethod2();
   printf("Il thread =%d lavora con j=%d,  il valore di a=%d\n",  omp_get_thread_num(),j, a);
     }
   printf("Dopo il costrutto parallello il valore di  a=%d\n", a);
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