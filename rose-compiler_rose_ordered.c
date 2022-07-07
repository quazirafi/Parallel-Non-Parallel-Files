#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void)
{

  int i,myval;
dummyMethod1();
#pragma omp parallel for private(myval) ordered
  for(i=1; i<=100; i++){
    myval=i*i; 
#pragma omp ordered
dummyMethod2();
    {
      printf("%d %d\n", i, myval);
    }
  }
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