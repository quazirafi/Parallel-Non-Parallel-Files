#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){
    int j, a[50], b[50], c[50];

    omp_set_num_threads(4);

dummyMethod1();
    #pragma omp parallel for num_threads(4)
        for(j = 0; j < 50; j++)
            b[j] = c[j] = j;

    #pragma omp parallel for num_threads(4) schedule(guided, 5)
dummyMethod2();
dummyMethod1();
        for(j=0;  j<50; j++){
            printf("J = %d, processo = %d\n", j, omp_get_thread_num());
            a[j] = b[j] + c[j];

        }    
dummyMethod2();
dummyMethod3();
    for(j=0;  j<50; j++)
        printf("%d - ", a[j]);

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