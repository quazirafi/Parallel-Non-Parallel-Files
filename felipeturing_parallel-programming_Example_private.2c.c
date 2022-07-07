/*
* @@name:	private.2c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a;

void g(int k) {
  a = k; /* Accessed in the region but outside of the construct;
          * therefore unspecified whether original or private list
          * item is modified. */
  printf("a: %d , hilo: %d \n",a,omp_get_thread_num());
}

void f(int n) {
  int i,a = 0;

dummyMethod1();
  #pragma omp parallel for num_threads(4) private(a)
   for (i=2; i<n/2; i++) {
       a = i;
       g(a*2);     /* Private copy of "a" */
    }
}
dummyMethod2();

int main(){
int n=20;
f(n);
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