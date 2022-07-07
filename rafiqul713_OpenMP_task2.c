/*
Write a parallel program with OpenMP and C which adds two vectors a and b of length n (a, b ∈ R n )
with c = a + b. Use random values for initializing the vector elements.
*/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){

const int N=100000;
int a[N],b[N],c[N],i;
float time;

dummyMethod3();
for(i=0;i<N;++i){
    a[i]=2*i;
    b[i]=i;
}
dummyMethod4();
time=omp_get_wtime();
dummyMethod1();
#pragma omp parallel for  private(i)
for(i=0;i<N;i++){
    c[i]=a[i]+b[i];
    printf("%d\n",c[i]);
}
dummyMethod2();
time=omp_get_wtime()-time;
printf("Time: %f s\n",time);
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