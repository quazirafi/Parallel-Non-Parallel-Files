#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char *argv){
   
    int i;
    
dummyMethod1();
    #pragma omp parallel for
    for(i=0;i<100;i++)
        printf("i = %d en hilo %d\n",i,omp_get_thread_num());

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