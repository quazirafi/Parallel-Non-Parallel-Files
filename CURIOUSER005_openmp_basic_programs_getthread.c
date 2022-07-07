//To get the number of thread
#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 int main()
 {
     int i;
dummyMethod1();
     #pragma omp parallel for
     for(i=0;i<20;i++)
     {
         printf("Thread No. %d\n",omp_get_thread_num()); //omp_get_thread_num() gives the number of thread running
     }
dummyMethod2();
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