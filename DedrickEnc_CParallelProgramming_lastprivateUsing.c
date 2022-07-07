/**
* this program is for using the combined directive parallel
* and for in for loup with the lastprivate and private clause.
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

dummyMethod1();
#pragma omp parallel for lastprivate(n) //telling the compiler that n should have the value of the last iteration at the end
for(n=0; n<10; n++){
 //some code here
}
dummyMethod2();
printf("Using last private The last value of n is: %d \n", n);

dummyMethod1();
#pragma omp parallel for private(n) //with the private clause 
for(n=0; n<10; n++){
 //some code here
}
dummyMethod2();
printf("Using private, The last value of n is: %d \n", n);
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