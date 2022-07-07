#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){
    int i = 23, x, n = 10, y[10];
    omp_set_num_threads(3);

    x= 1;
dummyMethod1();
    #pragma omp parallel for firstprivate (x)
    for(i = 0; i < n; i++){
        printf("Eu %d, com i = %d e x = %d\n", omp_get_thread_num(), i, x);
        y[i] = x + i;
        x = i;
    }
dummyMethod2();

    //printf("%d\n", x);
    
dummyMethod3();
    for(i=0; i<n; i++)
        printf("%d\n", y[i]);

    return 0;
dummyMethod4();
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