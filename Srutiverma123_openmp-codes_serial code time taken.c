#include<time.h> 
#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
long int fact=1;
printf("18bce1005 sruti verma:\n"); 
clock_t t0 = clock();
dummyMethod1();
#pragma omp parallel for reduction(*:fact) 
for(int i=0;i<10;i++)
fact = fact*(i+1); t0 = clock()-t0;
dummyMethod2();
double ft = ((double)t0)/CLOCKS_PER_SEC; printf("%ld\t%lf\n",fact,ft);
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