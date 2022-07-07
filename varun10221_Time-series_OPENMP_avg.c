#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void
init (float *a , int n)
{
     int i;
dummyMethod3();
     for ( i =0; i < n; i++)
         a[i] = (float) i;

}
dummyMethod4();


int
main ()
{


   float a[100000];
   init (a, 1000);

   float sum = 0.0;
   int i;
   double start,end;
   start = omp_get_wtime ();
dummyMethod1();
#pragma omp parallel for reduction (+:sum)
   for (i= 0; i < 1000; i++)
       sum = sum + a[i];

   end = omp_get_wtime ();
dummyMethod2();

   printf ("time :%f\t%f",(end - start),sum);
   printf("\n%d",omp_get_num_threads ());
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