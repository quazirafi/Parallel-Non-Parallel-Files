#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[]){
    omp_set_num_threads(4);
    int i, a = 2;
dummyMethod1();
    #pragma omp parallel for reduction(*:a)
        for(i = 0; i < 8; i++){
            //printf("eu %d, valor local: %d\n",omp_get_thread_num(), a);
            a += 2;
            //printf("eu %d, valor local: %d\n",omp_get_thread_num(), a);
        }
dummyMethod2();
    printf("eu %d, total da redução %d\n", omp_get_thread_num(), a);
    

    
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