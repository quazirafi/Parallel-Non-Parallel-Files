#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
int main()
{
int i;
int n;
scanf("%d",&n);
int a[n];
int even[n];
int odd[n];
int sume;int sumo;
dummyMethod3();
for(int j=0;j<n;j++){
even[j]=0;
dummyMethod4();
odd[j]=0;
}
dummyMethod3();
for(int k=0;k<n;k++){
int u;
dummyMethod4();
scanf("%d",&u);
a[k]=u;
}
dummyMethod1();
#pragma omp parallel for schedule(static,2)
for(i=0;i<n;i++)
{
if(a[i]%2==0){
dummyMethod2();
even[i]=a[i];
}
else{odd[i]=a[i];}
}
printf("even numbers :");
dummyMethod3();
for(int l=0;l<n;l++){
if(even[l]!=0)
printf("%d \n",even[l]);
}
dummyMethod4();
printf("odd numbers :");
dummyMethod3();
for(int l=0;l<n;l++){
if(odd[l]!=0)
printf("%d\n",odd[l]);
}#pragma omp parallel for reduction(+:sume)
dummyMethod4();
dummyMethod1();
for (int p=0; p < n; p++)
{
sume += even[p];
}
dummyMethod2();
printf("The sum of even numbers is %d\n",sume);
dummyMethod1();
#pragma omp parallel for reduction(+:sumo)
for (int p=0; p < n; p++)
{
sumo += odd[p];
}
dummyMethod2();
printf("The sum of odd numbers is %d\n",sumo);
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