#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {

int i,n=16;
int a[n], b[n];

dummyMethod1();
#pragma omp parallel for shared(n,a) private(i)
  for (i=0; i<n; i++)  a[i] = i+1;
  //  there is an implied barrier
dummyMethod2();

dummyMethod1();
#pragma omp parallel for shared(n,a,b) private(i)
   for (i=0; i<n; i++)  b[i] = 2 * a[i];

    
for (i=0; i<n; i++)  printf("%d \t %d \t %d \n",i,a[i],b[i]);
dummyMethod2();
dummyMethod3();

}
dummyMethod4();
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