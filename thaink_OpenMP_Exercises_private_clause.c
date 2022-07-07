#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	int j,tmp = 0;
dummyMethod1();
	#pragma omp parallel for private(tmp)
	for (j = 0; j < 1000; ++j)
		tmp += j;
	printf("%d\n", tmp);
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