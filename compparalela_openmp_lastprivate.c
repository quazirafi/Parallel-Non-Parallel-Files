#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
   int a[10], b[10], c[10];
   int n = 10;
   int i;

dummyMethod1();
   #pragma omp parallel for shared(a,b,c,n) lastprivate(i)
   for(i = 0; i < n; i++){
      c[i] = a[i] + b[i];
   }
dummyMethod2();
   
   printf("Depois da região paralela ... i = %d\n", i);
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