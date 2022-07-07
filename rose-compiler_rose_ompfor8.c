#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern double f (double, double);

void foo(int nthreads, int size, int numiter, double *V, int totalSize)
{
int i, iter; 
for(iter=0; iter<numiter; iter++) {

dummyMethod1();
#pragma omp parallel for default(none) shared(V,totalSize) private(i) schedule(static) ordered
        for (i=0; i<totalSize-1; i++) {
                V[i] = f(V[i],V[i-1]);
                }

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