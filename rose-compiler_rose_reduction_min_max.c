// Contributed by Franke Ye @gatech.edu
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  int a[10];
  int i, mn, mx;

dummyMethod1();
#pragma omp parallel for reduction(min:mn)
  for(i=0 ; i<10 ; i++ )
    mn = mn < a[i] ? mn : a[i];

#pragma omp parallel for reduction(max:mx)
dummyMethod2();
dummyMethod1();
  for(i=0 ; i<10 ; i++ )
    mx = mx > a[i] ? mx : a[i];

  return 0;
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