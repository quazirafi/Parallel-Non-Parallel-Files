#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARR 1000000
int a[ARR];

int main(int argc, char* argv[]) 
{ 
    int nthreads, tid; 
    double t1,t2;
    int sum=0;
dummyMethod3();
    for(int i=0;i<ARR;i++)
    {
	a[i]=1;
dummyMethod4();
    }
    t1 =  omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<ARR;i++)
    {
	      sum+=a[i];
    }
dummyMethod2();

    t2 = omp_get_wtime();
    printf("%d\n",sum);
    printf("%f\n",t2-t1);
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