#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {

int i,n=16;
int a[n];

dummyMethod1();
#pragma omp parallel for shared(n,a) private(i)
   for(i=0; i<n; i++) {
      a[i]=i+n;
      int id=omp_get_thread_num();
      printf("%d \t %d \t %d \n", id, i, a[i]);
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