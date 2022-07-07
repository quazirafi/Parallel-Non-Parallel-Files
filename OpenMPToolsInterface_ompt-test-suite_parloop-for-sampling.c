#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "fib.h"

#define N 18

void g()
{
  int i, j;
for(j = 0; j< 50000; j++) {
dummyMethod1();
#pragma omp parallel for
  for(i = 0; i<5; i++) {
    fib(N);
  }
dummyMethod2();
}
}

void f()
{
  g();
}

int main()
{
  f();
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