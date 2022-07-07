#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int vmul(int*a, int*b, int*c, int N, int kk){
   int k;
   k=kk;
#pragma omp target map(to: a[0:N],b[0:N]) map(from:c[0:N])
dummyMethod1();
#pragma omp teams distribute parallel for firstprivate(k)
   for(int i=0;i<k;i++) {
      c[i]=a[i]*b[i]+k;
   }
dummyMethod2();
   return ++k;
}

int main(){
    const int N = 100000;
    int a[N],b[N],c[N],validate[N],kk;
    int k = N;
    int flag=-1; // Mark Success
dummyMethod3();
    for(int i=0;i<N;i++) {
        a[i]=i+1;
        b[i]=i+2;
        validate[i]=a[i]*b[i]+k;
    }
dummyMethod4();

    kk=vmul(a,b,c,N,k);

							dummyMethod3();
    for(int i=0;i<k;i++) {
        if(c[i]!=validate[i]) {
//          print 1st bad index
            if( flag == -1 ) 
              printf("First fail: c[%d](%d) != validate[%d](%d)\n",i,c[i],i,validate[i]);
            flag = i;
        }
    }
							dummyMethod4();
    if( flag != -1 ){
        printf("Last fail: c[%d](%d) != validate[%d](%d)\n",flag,c[flag],flag,validate[flag]);
    } 
    if( kk != k+1 ) {
        printf("Firstprivate variable fail: k(%d) != %d\n",kk,k);
    }
    if( flag != -1 || kk != k+1 ){
        printf("Fail\n");
        return 1;
    } else {
       printf("Success\n");
       return 0;
    }
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