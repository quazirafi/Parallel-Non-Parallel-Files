#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[])
{
    int thread_count=10;
    const int n=100;
    int x[n];
dummyMethod3();
    for(int i=0;i<n;i++)
    {
        x[i]=1;
    }
dummyMethod4();
    int sum=0;

    printf("within %d threads and vector of size %d each element of value 1 \n",thread_count,n);

dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) schedule (static,2)

    for(int i=0; i<n;i++)
    {
        sum +=x[i];
    }
dummyMethod2();

    printf("sum = %d",sum);
    printf("\n");
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