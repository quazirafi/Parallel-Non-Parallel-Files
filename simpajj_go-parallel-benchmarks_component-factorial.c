#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int factorial(int);

#define RANGE 1000

int main(int argc, char const *argv[])
{
	int i, j;
	const int N = atoi(argv[1]);
	int iCPU = omp_get_num_procs();
  omp_set_num_threads(iCPU);
	omp_set_dynamic(0);

dummyMethod3();
	for (i = 0; i <= N; i++)
		for(j = 0; j < RANGE; j++)
			factorial(j);
	
	return 0;
dummyMethod4();
}

int factorial(int num)
 {
   int fac = 1, n;
dummyMethod1();
   #pragma omp parallel for reduction(*:fac)
   for(n = 2; n <= num; ++n)
     fac *= n;
   return fac;
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