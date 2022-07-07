#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
  
int main(int argc, char* argv[]) 
{
int i,id;
int a[10]; 
omp_set_num_threads(3);
dummyMethod1();
#pragma omp parallel for private(i,id) shared(a)schedule(dynamic,2)
for (i=0;i<12;i++)
{
id=omp_get_thread_num();
dummyMethod2();
a[i] = i; // updating private a
printf("a[%d] is %d from thread: %d\n",i,a[i],id); 
}
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