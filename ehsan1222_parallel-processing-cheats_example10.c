#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void) {
    int A[] = {1, 2, 3, 4};
    int sum = 0;
    int i;

    // dependent for loop
dummyMethod1();
    #pragma omp parallel for num_threads(2) reduction(+: sum)
    for(i = 0; i< 4; i++) {
        sum += A[i];
    }
dummyMethod2();

    printf("Sum: %d\n", sum);

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