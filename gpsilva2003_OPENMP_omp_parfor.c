#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void saxpy(int n, float a, float * restrict x, float * restrict y)
{
dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i)
        y[i] = a*x[i] + y[i];
}
dummyMethod2();
    
int main(int argc, char *argv[]) { /* omp_parfor.c  */
int n = 1<<20; // 1 milhão de floats
float *x = (float*)malloc(n*sizeof(float));
float *y = (float*)malloc(n*sizeof(float));
dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        x[i] = 2.0f;
        y[i] = 1.0f;
    }
dummyMethod2();
    saxpy(n, 3.0f, x, y);
    free(x);
    free(y);
    return(0);
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