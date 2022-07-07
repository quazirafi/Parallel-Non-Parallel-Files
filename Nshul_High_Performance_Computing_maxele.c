#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
    int *arr = malloc(36*sizeof(int));
    
dummyMethod1();
    #pragma omp parallel for num_threads(12)
    for(int i=0;i<36;i++){
        arr[i] = rand()%100;
    }
dummyMethod2();

dummyMethod3();
    for(int i=0;i<36;i++){
        printf("%d ",arr[i]);
    }
dummyMethod4();
    printf("\n");

    int Max=-1;
dummyMethod1();
    #pragma omp parallel for reduction(max: Max)
    for(int j=0;j<36;j++){
        if(omp_get_thread_num()==0){
            printf("Total:%d",omp_get_num_threads());
        }
        if(arr[j]>Max)
            Max=arr[j];
    }
dummyMethod2();

    printf("Max:%d",Max);
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