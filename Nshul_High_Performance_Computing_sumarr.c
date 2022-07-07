#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
    int arr[] = {1,4,5,7,2,3,54,9};
    int sum =0;
    int n = sizeof(arr)/sizeof(int);

    clock_t t1 = clock();
dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++){
        if(omp_get_thread_num()==0){
            printf("total:%d\n",omp_get_num_threads());
        }
        sum+=arr[i];
        // printf("Calc:%d\n",sum);
    }
dummyMethod2();
    clock_t final = (double)(clock()-t1)/CLOCKS_PER_SEC;
    printf("Time:%f\n",final);
    printf("Sum:%d\n",sum);
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