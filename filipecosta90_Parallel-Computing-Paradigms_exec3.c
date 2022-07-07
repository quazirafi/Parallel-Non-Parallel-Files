#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (){

  int result[100];
dummyMethod1();
#pragma omp for parallel schedule ( dynamic, 1 )
  for ( int i = 0; i < 100; i++ ) {
    result[i] = sin (i );
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