#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main()
{
  int i=0;
  int s=2;
  int e=50000;

  int j=0,count1=0,pc=0;

dummyMethod1();
  #pragma omp parallel for reduction(+:pc)
  for(i=2; i<=e; i++) {
    int count1 = 0;
    for(j=1; j<=i; j++) {
       if((i%j) == 0) {
           count1++;
       }
    }
    if(count1 == 2) {
        pc++;
    }
}
dummyMethod2();
  printf("%d\n",pc);
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