#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(){
long long n=10000;
double start,end;
long long a[n],b[n],c[n],sume=0;
dummyMethod3();
for(long long i=0;i<n;i++){
a[i]=rand();
dummyMethod4();
}
dummyMethod3();
for(long long i=0;i<n;i++){
b[i]=rand();
dummyMethod4();
}
start=omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:sume)
for(long long i=0;i<n;i++){
c[i]=a[i]*b[i];
dummyMethod2();
sume+=c[i];
}
end=omp_get_wtime();
printf("Time taken : %lf\n",end-start);
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