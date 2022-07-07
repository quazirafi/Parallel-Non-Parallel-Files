#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1024
int main()
{
   float *a, *b, *c;
   int i;
   
   a = (float*) malloc(N * sizeof(float));
   b = (float*) malloc(N * sizeof(float));   
   c = (float*) malloc(N * sizeof(float));
   
// initialize a, b, and c (code not shown)

#pragma omp target map(to:a[0:N],b[0:N]) map(tofrom:c[0:N])
dummyMethod1();
#pragma omp teams distribute parallel for simd
   for (i = 0; i < N; i++)
      c[i] += a[i] * b[i];
}
dummyMethod2();
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