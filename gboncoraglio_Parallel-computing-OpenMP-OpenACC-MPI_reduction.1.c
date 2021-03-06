#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void reduction1(float *x, int *y, int n){
    int i, b, c;
    float a, d;
    a = 0.0;
    b = 0;
    c = y[0];
    d = x[0];
dummyMethod1();
    #pragma omp parallel for private(i) shared(x, y, n) \
            reduction(+:a) reduction(^:b) \
            reduction(min:c) reduction(max:d)

    for (i=0; i<n; i++) {
        a += x[i];
        b ^= y[i];
        if(c>y[i]) c=y[i];
        d = fmaxf(d,x[i]);
    }
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