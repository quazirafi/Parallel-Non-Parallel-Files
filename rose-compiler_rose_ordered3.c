#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void)
{
  int i,j, myval;
dummyMethod1();
#pragma omp parallel for private(myval) ordered(2)
  for(i=1; i<=100; i++)
    for(j=1; j<=100; j++)
    {
      myval=i*j; 
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