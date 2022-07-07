#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int i;
int j;
int a[100][100];

void foo()
{
  
dummyMethod1();
#pragma omp parallel for private (i)
  for (i = 0; i <= 99; i += 1) {
    for (j = 0; j <= 99; j += 1) {
      a[i][j] = a[i][j] + 1;
      if (a[i][j] == 100) 
        break; 
    }
  }
dummyMethod2();
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