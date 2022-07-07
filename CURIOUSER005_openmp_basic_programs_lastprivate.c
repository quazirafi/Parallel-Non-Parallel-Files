//To see the Last private
#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 int main()
 {
     int i,a=10,b=5;
dummyMethod1();
     #pragma omp parallel for lastprivate(a) num_threads(1) //this step is for parallelising
     for(i=1;i<5;i++)
     {
         a = a+b;                    //It takes initial value of a as 0 and not 10
         printf("A is after %d iteration : %d\n",i,a);
     }
dummyMethod2();
     printf("A outside firstprivate is %d\n",a);  //gives output of fr loop
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