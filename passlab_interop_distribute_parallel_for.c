#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
float dotprod(float B[], float C[], int N)
{
    float sum = 0;
    int i;
    #pragma omp target teams map(to: B[0:N], C[0:N]) defaultmap(tofrom:scalar) reduction(+:sum)
dummyMethod1();
    #pragma omp distribute parallel for reduction(+:sum)
    for (i=0; i<N; i++)
        sum += B[i] * C[i];
    return sum;
dummyMethod2();
}

 /* Note: The variable sum is now mapped with tofrom from the defaultmap
 clause on the combined target teams construct, for correct
 execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.
 */
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