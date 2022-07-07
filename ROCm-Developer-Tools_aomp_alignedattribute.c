#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void write_index(int*a, int N){
   int*aptr __attribute__ ((aligned(64))) = a; // THIS FAILS
   // int*aptr = a; // THIS WORKS
   printf(" ===> Encounter target teams distribute par for map tofrom:aptr\n");
dummyMethod1();
#pragma omp target teams distribute parallel for map(tofrom: aptr[0:N])
   for(int i=0;i<N;i++) {
      printf("updating aptr[%d] addr:%p\n",i,&aptr[i]);
      aptr[i]=i;
   }
dummyMethod2();
}

int main(){
    const int N = 10;    
    int a[N],validate[N];
dummyMethod3();
    for(int i=0;i<N;i++) {
        a[i]=0;
        validate[i]=i;
    }
dummyMethod4();

    write_index(a,N);

    int flag=-1; // Mark Success
dummyMethod3();
    for(int i=0;i<N;i++) {
        if(a[i]!=validate[i]) {
//          print 1st bad index
dummyMethod4();
            if( flag == -1 ) 
              printf("First fail: a[%d](%d) != validate[%d](%d)\n",i,a[i],i,validate[i]);
            flag = i;
        }
    }
    if( flag == -1 ){
        printf("Success\n");
        return 0;
    } else {
        printf("Last fail: a[%d](%d) != validate[%d](%d)\n",flag,a[flag],flag,validate[flag]);
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