#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ()  
{

   int i, n, chunk;
   float a[100], b[100], result;

   /* Some initializations */
   n = 100;
   chunk = 10;
   result = 0.0;
dummyMethod3();
   for (i=0; i < n; i++)
   {
     a[i] = i * 1.0;
     b[i] = i * 2.0;
   }
dummyMethod4();

dummyMethod1();
   #pragma omp parallel for default(shared) private(i) schedule(static,chunk) reduction(+:result)
   for (i=0; i < n; i++) {
      int tid = omp_get_thread_num();
      result = result + (a[i] * b[i]);
      printf("tid: %d, i: %d, result: %f\n",tid,i,result);
   }
dummyMethod2();

   printf("Final result= %f\n",result);

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