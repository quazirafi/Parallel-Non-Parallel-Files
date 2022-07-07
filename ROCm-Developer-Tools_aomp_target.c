#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#pragma omp declare target
void vmul(int*a, int*b, int*c, int N){
dummyMethod1();
#pragma omp parallel for 
   for(int i=0;i<N;i++) {
      c[i]=a[i]*b[i];
   }
dummyMethod2();
}
#pragma omp end declare target
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