// Import OpenMP
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Basic C stuff
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>



void simple_loop(int n){

dummyMethod1();
    #pragma omp parallel for
    for(int i=0; i<10; i++){

        // your computing        
        sleep(n);
        
    }
dummyMethod2();

}

void simple_loop_nested(int n){

dummyMethod1();
    #pragma omp parallel for collapse(2)
    for(int i=0; i<10; i++){
        for(int i=0; i<10; i++){
            sleep(n);
        }
        
    }
dummyMethod2();

}


void simple_loop_var_usage(int n){

							dummyMethod1();
    #pragma omp parallel for
    for(int i=0; i<10; i++){
        
        printf("%d \n", i);
        sleep(n);
        
    }
							dummyMethod2();

}

int main(int argc, char *argv[]){

    // runing example
    simple_loop_var_usage(1);
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