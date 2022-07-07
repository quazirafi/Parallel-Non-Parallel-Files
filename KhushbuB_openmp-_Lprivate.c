#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main()
{

	int i=3, n;
	omp_set_num_threads(1); 
dummyMethod1();
	#pragma omp parallel for lastprivate(i)
	
		for(n=1; n<5; n++)
		{
			printf("In loop 'i' is = %d \n", i);
			i=i+2;
   		}
	
	printf("Out of loop 'i' is = %d \n", i);
dummyMethod2();
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