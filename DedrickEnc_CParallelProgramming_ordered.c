/**
* this program is for using the ordered directive
**/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
 float intermediate = 0, sum;
int i;

dummyMethod1();
 #pragma omp parallel for ordered private(intermediate) 
	 for(i=0; i<10; i++){
	  #pragma omp ordered
	   {
	    sum = intermediate +sum;
	    
	   }

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