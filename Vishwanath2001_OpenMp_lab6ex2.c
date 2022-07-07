#include<stdio.h>
#include "omp.h"
#include <stdlib.h>
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char const *argv[])
{
    int i;
    int arr[1000000];
    
dummyMethod3();
    for(int i=0;i<1000000;i++){
        arr[i]=rand();
    }
dummyMethod4();
    float sum=0.0,mean,SD=0.0;
dummyMethod1();
    #pragma omp parallel for num_threads(3) reduction(+:sum)
    for(int k=0;k<1000000;++k){
        sum += arr[k];

    }
dummyMethod2();
    mean=sum/10;
dummyMethod1();
    #pragma omp parallel for num_threads(3) reduction(+:SD)
    for(int j=0;j<1000000;j++){
        SD += pow(arr[i] - mean, 2);
    }
dummyMethod2();
    
    printf("%f",sqrt(SD/10));
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