#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char *argv){
   
    int i,k,suma;
    
    puts("--- Sin constructo Atomic ---");
    for(k=0;k<5;k++){
        suma = 0;
dummyMethod1();
        #pragma omp parallel for
        for(i=0;i<500000;i++)
            suma = suma + i;

        printf("Suma total: %d\n",suma);
dummyMethod2();
    }

    puts("--- Con constructo Atomic ---");
    for(k=0;k<5;k++){
        suma = 0;
        #pragma omp parallel for
        for(i=0;i<500000;i++)
            #pragma omp atomic
            suma = suma + i;

        printf("Suma total: %d\n",suma);
    }
    
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