#include<stdio.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int i;
    int x[2000000];
    for(i=0; i<2000000; i++)
dummyMethod1();
        x[i]=2;

    #pragma omp parallel for
dummyMethod3();
    for(i=0; i<2000000; i++)
        x[i] = sqrt(x[i])+ sqrt(x[i])+ sqrt(x[i])*100;

dummyMethod4();
return 0;
dummyMethod2();
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