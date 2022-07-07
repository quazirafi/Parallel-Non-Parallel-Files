#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void veccpy2(int *a, int *b, int n) {

   int j;
dummyMethod1();
   #pragma omp parallel for
   for( j = n/2; j<n;j++) {
      b[j]= a[j];
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