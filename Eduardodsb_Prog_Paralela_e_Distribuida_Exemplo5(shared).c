#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
   int i, n = 7;
   int a[n];
   (void) omp_set_num_threads(4);
dummyMethod3();
   for (i=0; i<n; i++)
            a[i] = i+1;
   #pragma omp parallel for shared(a) /*Divide o for igualmente para cada thread executar um intervalo.*/
dummyMethod4();
dummyMethod1();
   for (i=0; i<n; i++)  {
       a[i] += i;
   } /*-- End of parallel for --*/
dummyMethod2();
   printf("No programa principal depois do parallel for:\n");
dummyMethod3();
   for (i=0; i<n; i++)   printf("a[%d] = %d\n",i,a[i]);
   return(0);
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