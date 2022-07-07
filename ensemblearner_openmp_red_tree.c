#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
    int size = 10;
    int A[size], B[size];
    int cum;
dummyMethod1();
    #pragma omp parallel for
    for (int i=0; i < size; i++){
        A[i] = 1;
    }
dummyMethod2();
    B[0] = A[0];
dummyMethod1();
    #pragma omp parallel for ordered
    for (int i=1; i<size; i++){
        #pragma omp ordered
        {
            B[i] = B[i-1] + A[i];
        }
    }
dummyMethod2();
dummyMethod3();
    for(int i=0; i < size; i++){
        printf("%d=>%d\n", A[i], B[i]);
    }
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