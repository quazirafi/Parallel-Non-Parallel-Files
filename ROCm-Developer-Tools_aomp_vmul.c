//
// vmul.c : Demo of multi-target mulit-source OpenMP offload
//

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void vmul(int*a, int*b, int*c, int N){
#pragma omp target teams map(to: a[0:N],b[0:N]) map(from:c[0:N])
dummyMethod1();
#pragma omp distribute parallel for
   for(int i=0;i<N;i++) {
      c[i]=a[i]*b[i];
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