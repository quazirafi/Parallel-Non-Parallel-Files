#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void vmul(int*a, int*b, int*c, int N){
#pragma omp target map(to: a[0:N],b[0:N]) map(from:c[0:N*N])
dummyMethod1();
#pragma omp teams distribute parallel for collapse(2)
   for(int i=0;i<N;i++)
     for(int j=0;j<N-i;j++){
      c[i*N+j]=a[i]*b[j];
   }
dummyMethod2();
}

int main(){
    const int N = 1000;
    int a[N],b[N],c[N*N],validate[N*N];
    int flag=-1; // Mark Success
dummyMethod3();
    for(int i=0;i<N;i++){
      a[i]=i+1;
      for(int j=0;j<N-i;j++){
        b[j]=j+2;
        validate[i*N+j]=a[i]*b[j];
      }
    }
dummyMethod4();

    vmul(a,b,c,N);

							dummyMethod3();
    for(int i=0;i<N;i++){
      for(int j=0;j<N-i;j++){
            if( validate[i*N+j] != a[i]*b[j])
              printf("First fail: c[%d](%d) != validate[%d](%d)\n",i,c[i],i,validate[i]);
            flag = i;
        }
    }
							dummyMethod4();
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