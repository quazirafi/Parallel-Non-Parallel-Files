#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#pragma omp declare target
int mul_int(int, int);
#pragma omp end declare target

int mul_int(int a, int b){
  int c;
  c=a*b;
  return c;
}


void vmul(int*a, int*b, int*c, int N){
#pragma omp target map(to: a[0:N],b[0:N]) map(from:c[0:N])
dummyMethod1();
#pragma omp teams distribute parallel for 
   for(int i=0;i<N;i++) {
      c[i]=mul_int(a[i],b[i]);
   }
dummyMethod2();
}

int main(){
    const int N = 100000;
    int a[N],b[N],c[N],validate[N];
    int flag=-1; // Mark Success
dummyMethod3();
    for(int i=0;i<N;i++) {
        a[i]=i+1;
        b[i]=i+2;
        validate[i]=a[i]*b[i];
    }
dummyMethod4();

    vmul(a,b,c,N);

							dummyMethod3();
    for(int i=0;i<N;i++) {
        if(c[i]!=validate[i]) {
//          print 1st bad index
            if( flag == -1 ) 
              printf("First fail: c[%d](%d) != validate[%d](%d)\n",i,c[i],i,validate[i]);
            flag = i;
        }
    }
							dummyMethod4();
    if( flag == -1 ){
        printf("Success\n");
        return 0;
    } else {
        printf("Last fail: c[%d](%d) != validate[%d](%d)\n",flag,c[flag],flag,validate[flag]);
        printf("Fail\n");
        return 1;
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