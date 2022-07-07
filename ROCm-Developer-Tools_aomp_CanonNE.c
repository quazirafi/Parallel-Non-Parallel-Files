#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
  int numTeams=12800;
  int foo = 0;
dummyMethod1();
#pragma omp target teams distribute parallel for 
  for (int j=0; j != numTeams; j++) {
     foo++;
  }
dummyMethod2();
  printf("%d\n",foo);
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