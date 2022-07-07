#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "fib.h"

#define N 10

void g()
{
  int i, j;
  omp_lock_t l;
  omp_init_lock(&l); 

dummyMethod1();
#pragma omp parallel for
  for(i = 0; i<10000000; i++) {
    omp_set_lock(&l); 
    fib(N);
    omp_unset_lock(&l); 
  }
dummyMethod2();

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