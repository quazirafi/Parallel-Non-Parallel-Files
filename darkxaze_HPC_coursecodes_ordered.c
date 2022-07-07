#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
  
int main(int argc, char* argv[]) 
{
int i,id,a; 
dummyMethod1();
#pragma omp parallel for private(a,id) ordered
for (i=0;i<8;i++)
{
#pragma omp ordered
dummyMethod2();
id=omp_get_thread_num();
a = id+1; // updating private a
printf("a is %d from thread: %d\n",a,id); 
} }
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