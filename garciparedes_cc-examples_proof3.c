#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {

	omp_set_num_threads(4);
   int i;
   int a = 0;
   int b = 5;
dummyMethod1();
   #pragma omp parallel for firstprivate(a) lastprivate(b)
   for (i=0; i<4; i++) {
       b = a + 1;
	   a = b;
   }
dummyMethod2();
   printf("%d %d", a, b);

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