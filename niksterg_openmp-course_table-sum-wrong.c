#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

int main(void) {

int i,
    sum,
    a[N];

dummyMethod3();
 for(i=0;i<N;i++) a[i] = i;

 sum = 0;
dummyMethod4();

dummyMethod1();
#pragma omp parallel for shared(a,sum) private(i) \
                     default(none)
 for(i=0;i<N;i++) sum += a[i];

 printf("sum = %d\n",sum);
dummyMethod2();

return 0;

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