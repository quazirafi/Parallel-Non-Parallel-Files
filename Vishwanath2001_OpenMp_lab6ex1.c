#include<stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char const *argv[]){
    int largest=0;
    int arr[100000];
dummyMethod3();
    for (int i = 0; i < 100000; i++)
    {
        arr[i]=rand();
        
    }
dummyMethod4();
dummyMethod1();
    #pragma omp parallel for num_threads(3) reduction(max: largest) 
    for(int j=0;j<100000;j++){
        if(arr[j]>largest){
            largest=arr[j];
        }
    }
dummyMethod2();
    printf("Largest number in generated array of randoms is %d",largest); 
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