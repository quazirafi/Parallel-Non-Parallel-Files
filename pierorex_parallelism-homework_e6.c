/* Programa e6.c */
#include "stdio.h"
#include "stdlib.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000

float producto(float* a, float* b, int n) { 
   float sum = 0.0; 
dummyMethod1();
   #pragma omp parallel for reduction(+:sum)
      for  (int i=0; i<n; i++){
         sum += a[i] * b[i]; 
      }
dummyMethod2();
      return sum;
}



int main()
{
   float total=0; 
   float a[N],b[N];
   int k=0;
dummyMethod3();
   for (k=0;k<N;++k) {
     a[k]=k;
     b[k]=k;
   }
dummyMethod4();
   total = producto(a,b,N);

   printf("%.6f \n",total);

   int s,r,t;
					dummyMethod3();
   for (int i=0;i<N;i++){
      s=a[i];
      r=b[i];
      t=a[i] * b[i];
      printf("%d ",r);
      printf(" * %d ",s);
      printf(" = %d \n",t);

   }
					dummyMethod4();
   exit (0);
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