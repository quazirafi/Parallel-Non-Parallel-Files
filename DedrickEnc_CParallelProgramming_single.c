/**
* this program is for using the single directive
**/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
int n; //variable for iteration
int sum = 0, sum2 = 0;

dummyMethod1();
#pragma omp parallel for //telling the compiler to execute the following bloc in parallel

for(n=0; n<10; n++){
 printf("iteration %d performed by the thread : %d \n", n, omp_get_thread_num());
 sum+=n;
}
dummyMethod2();
printf("The sum parallel is: %d \n", sum);

#pragma omp parallel
{
 #pragma omp single //telling the compiler that only one thread will execute this block
  {
dummyMethod3();
   for(n=0; n<10; n++){
    printf("iteration %d performed by the thread : %d \n", n, omp_get_thread_num());
    sum2+=n;
   }
dummyMethod4();
   printf("The sum single is: %d \n", sum2); 
  }
} 

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