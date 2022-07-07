#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ()
{
    const int n = 30;
    int   i,chunk;
    double a[n], b[n], result = 0.0;
    double results[10];

    /* Some initializations */
    chunk = 5;
dummyMethod3();
    for (i=0; i < n; i++) {
        a[i] = i * 3.14;
        b[i] = i * 6.67;
        results[i] = 0.0;
    }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for default(shared) private(i) schedule(static,chunk) reduction(+:results[:10])
    for (i=0; i < n; i++){
        int j;
        for (j=0; j < n; j++){
            ++results[j];
        }
    }
dummyMethod2();

    printf("Final result= %f\n",result);
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