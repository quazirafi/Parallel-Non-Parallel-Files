//
// Created by Mohit Singh on 8/18/15.
//

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int foo(int i){
    return i*i;
}
int main() {
    int i;
dummyMethod1();
   #pragma omp parallel for
        for(int i=0; i<5;i++){
            int ID = omp_get_thread_num();
            printf("Hello(%d) => %d\n", ID,i);
        }
dummyMethod2();

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