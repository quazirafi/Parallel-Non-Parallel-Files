#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void vset(int*b, int N){
#pragma omp target map(tofrom: b[0:N])
dummyMethod1();
#pragma omp teams distribute parallel for 
   for(int i=0;i<N;i++) {
      b[i]=i;
   }
dummyMethod2();
}

int main(){
    const int N = 100;    
    int b[N],validate[N];
    int flag=-1; // Mark Success
dummyMethod3();
    for(int i=0;i<N;i++) {
        b[i] = i;
        validate[i]=i;
    }
dummyMethod4();

    vset(b,0);

dummyMethod3();
    for(int i=0;i<N;i++) {
        if(b[i]!=validate[i]) {
//          print 1st bad index
dummyMethod4();
            if( flag == -1 ) 
              printf("First fail: b[%d](%d) != validate[%d](%d)\n",i,b[i],i,validate[i]);
            flag = i;
        }
    }
    if( flag == -1 ){
        printf("Success\n");
        return 0;
    } else {
        printf("Last fail: b[%d](%d) != validate[%d](%d)\n",flag,b[flag],flag,validate[flag]);
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