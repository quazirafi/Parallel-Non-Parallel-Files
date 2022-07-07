#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N           50
#define CHUNKSIZE   10

int main(int argc, char *argv[]){
    int i, chunk;
    float a[N], b[N], c[N];

dummyMethod3();
    for (i = 0; i < N; i++){
        a[i] = b[i] = i * 1.0;
    };
dummyMethod4();
    chunk = CHUNKSIZE;

dummyMethod1();
    #pragma omp parallel for              \
        shared(a, b, c, chunk) private(i) \
        schedule(static, chunk)

    for(i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    };
dummyMethod2();

dummyMethod3();
    for(i = 0; i < N; i++){
        printf("c[%d] = %f\n", i, c[i]);
    };
dummyMethod4();

    return 0;
};
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