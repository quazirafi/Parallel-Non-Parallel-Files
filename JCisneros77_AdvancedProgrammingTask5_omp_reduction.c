#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	srand(time(NULL));

	   int fac = 1;
dummyMethod1();
   #pragma omp parallel for reduction(*:fac)
   		for(int n=2; n<=25; ++n)
     		fac *= n;

  		printf("Factorial: %d\n",fac);
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