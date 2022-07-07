//To see the First private and private
    #include<stdio.h>
    #include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
     void main()
     {
         int i,a=10,b=5;
dummyMethod1();
         #pragma omp parallel for firstprivate(a) private(b) num_threads(1) //this is parallising step
         for(i=1;i<5;i++)
         {
             b++;  //In Linux it will assign value b=0 and then increament operator will work. This is functionality of private()
             a = a+b;
             printf("A is after %d iteration : %d\n",i,a);
         }
dummyMethod2();
         printf("A outside omp region is %d\n",a);
         
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