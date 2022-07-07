#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[]){
    omp_set_num_threads(4);
    int i;
dummyMethod1();
    #pragma omp parallel for /*Por padrão o índice do for é privado*/
        for(i = 0; i < 8; i++)
            printf("eu %d, fiz %d\n", omp_get_thread_num(), i);
    

    
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