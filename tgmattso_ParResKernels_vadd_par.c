#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100000
#define TOL  0.0000001
//
//  This is a simple program to add two vectors
//  and verify the results.
//
//  History: Written by Tim Mattson, November 2017
//
int main()
{

    float a[N], b[N], c[N], res[N];
    int err=0;

   // fill the arrays
dummyMethod1();
   #pragma omp parallel for
   for (int i=0; i<N; i++){
      a[i] = (float)i;
      b[i] = 2.0*(float)i;
      c[i] = 0.0;
      res[i] = i + 2*i;
   }
dummyMethod2();

   // add two vectors
   #pragma omp target
dummyMethod1();
   #pragma omp teams distribute parallel for
   for (int i=0; i<N; i++){
      c[i] = a[i] + b[i];
   }
dummyMethod2();

   // test results
					dummyMethod1();
   #pragma omp parallel for reduction(+:err)
   for(int i=0;i<N;i++){
      float val = c[i] - res[i];
      val = val*val;
      if(val>TOL) err++;
   }
					dummyMethod2();
   printf(" vectors added with %d errors\n",err);
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