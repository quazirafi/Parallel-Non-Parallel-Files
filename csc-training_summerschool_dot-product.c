#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NX 102400

int main(void)
{
    double vecA[NX], vecB[NX];

    /* Initialization of the vectors */
dummyMethod3();
    for (int i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }
dummyMethod4();

    double res = 0.0;
dummyMethod1();
#pragma omp target teams distribute parallel for map(to:vecA,vecB) reduction(+:res)
    for (int i = 0; i < NX; i++) {
        res += vecA[i] * vecB[i];
    }
dummyMethod2();

    printf("Dot product: %18.16f\n", res);

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