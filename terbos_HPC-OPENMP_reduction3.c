#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
main () { 
    int i, n, chunk, result3=0;
    float a[100], b[100], result1, result2;
    n = 100;
    chunk = 10;
    result1 = result2 = 0.0;
dummyMethod3();
    for (i=0; i < n; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }
dummyMethod4();
dummyMethod1();
    #pragma omp parallel for default(shared) private(i) schedule(static,chunk) \
            	reduction(+:result1, result2)  reduction (|:result3)
    for (i=0; i < n; i++) {
        result1 = result1 + a[i] ; 
        result2 = result2 + b[i];
        result3 = result3|i;
   }
dummyMethod2();
    printf("Finally, result1 = %f, result2 = %f, and result3 = %d\n",result1,result2,result3);
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