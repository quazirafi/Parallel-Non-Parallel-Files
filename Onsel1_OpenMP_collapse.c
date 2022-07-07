#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
 
int main(void){
int i;
int j;
dummyMethod1();
#pragma omp parallel for collapse(2) 
for(i=0;i<4;i++){
    for (j=0;j<8;j++){
        printf("Thread: %d, (i,j) = (%d,%d)\n",omp_get_thread_num(),i,j);
    }
}
dummyMethod2();
 printf("Done!");
 
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