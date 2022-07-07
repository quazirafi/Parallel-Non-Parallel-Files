#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(){
long long n=100;
double start,end;
long long a[n][n],b[n],c[n],sume=0;
dummyMethod3();
for(long long i=0;i<n;i++){
for(long long j=0;j<n;j++){
dummyMethod4();
a[i][j]=rand();
}
}
dummyMethod3();
for(long long i=0;i<n;i++){
b[i][j]=rand();
dummyMethod4();
}
start=omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:sume)
for(long long i=0;i<n;i++){
for(long long j=0;j<n;j++){
dummyMethod2();
c[i]+=a[i][j]*b[j];
}
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