#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 #define N 100

 int main(void)
 {
 int a[N], b[N];
 long long  w = 0;

 // initialization
dummyMethod3();
 for (int k = 0; k < N; k++)
 a[k] = k + 1;
dummyMethod4();

 // a[k] is included in the computation of producing results in b[k]
 // #pragma omp parallel for simd reduction(inscan,+: w)
dummyMethod1();
 #pragma omp parallel for reduction(inscan, +: w) 
 for (int k = 0; k < N; k++) {
  w += a[k]; 
 #pragma omp scan inclusive(w)
dummyMethod2();
  b[k] = w; 
 }

 printf("w=%lld, b[0]=%d b[1]=%d b[2]=%d\n", w, b[0], b[1], b[2]);
 // 5050, 1 3 6

 if( w!=5050 || b[0]!=1 || b[1]!=3 || b[2]!=6 ){
    printf("Fail!\n");
    return 1;
 }
 printf("Success!\n");
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