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
#pragma omp parallel for  private(i,id,a)
for (i=0;i<10;i++)
{
id=omp_get_thread_num();
dummyMethod2();
a = i+1; // updating private a
printf("a is %d for i= %d from thread: %d\n",a,i,id); 
} // writing out private a by each thread
printf("after: a is %d\n",a);// writing private a
}                            //outside parallel loop
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