#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif 
int counter=0;

#ifdef _OPENMP
#pragma omp threadprivate(counter)
#endif 
int main(void)
{
 int i;
dummyMethod1();
#pragma omp parallel for
 for(i=0;i<10000;i++)
    counter++;
#pragma omp parallel for
dummyMethod2();
dummyMethod1();
 for(i=0;i<10000;i++)
    counter+=3;
#pragma omp parallel
dummyMethod2();
  printf("counter=%d\n",counter);
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