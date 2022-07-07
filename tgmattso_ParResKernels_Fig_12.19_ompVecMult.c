#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1024
int main()
{
   float a[N], b[N], c[N];
   int i;

// initialize a, b, and c (code not shown)

#pragma omp target
dummyMethod1();
#pragma omp teams distribute parallel for simd
   for (i = 0;i < N; i++)
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