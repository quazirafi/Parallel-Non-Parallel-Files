#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
    const int N = 10000000;
    int i, a[N];
 
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N; i++)
        a[i] = 2 * i;
 
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