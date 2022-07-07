#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void teste(){
    int i, x[10] = {1,2,3,4,5,6,7,8,9,10}, N=10, maxval = 5;

dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N ; i ++)
        if (x [ i ] > maxval) 
            break; //break não pode ser utilizado com parallel for
}
dummyMethod2();

int main(int argc, char *argv[]){
    
    omp_set_num_threads(4);

    teste();

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