#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void a(int *x, int *y, int n) {
dummyMethod3();
    for (int i = 0; i < n - 1; i++) {
        x[i] = (y[i] + x[i + 1]) / 7;
    }
dummyMethod4();
}

void a_sol(int *x, int *y, int n) {
    int x2[n];
dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        x2[i] = x[i + 1];
    }
dummyMethod2();
dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        x2[i] = (y[i] + x2[i]) / 7;
    }
dummyMethod2();
}

void b(int *x, int *y, int *z, int n, int k) {
    int a;
dummyMethod3();
    for (int i = 0; i < n; i++) {
        a = (x[i] + y[i]) / (i + 1);
        z[i] = a;
    }
dummyMethod4();

    int f = sqrt(a + k);
}

void b_sol(int *x, int *y, int *z, int n, int k) {
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        z[i] = (x[i] + y[i]) / (i + 1);
    }
							dummyMethod2();
    int f = sqrt(z[n] + k);
}

void c(int *x, int *y, int n, int a, int b) {
							dummyMethod3();
    for (int i = 0; i < n; i++) {
        x[i] = y[i] * 2 + b * i;
    }
							dummyMethod4();

							dummyMethod3();
    for (int i = 0; i < n; i++) {
        y[i] = x[i] + a / (i + 1);
    }
							dummyMethod4();
}

void c_sol(int *x, int *y, int n, int a, int b) {
							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        x[i] = y[i] * 2 + b * i;
        y[i] = x[i] + a / (i + 1);
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