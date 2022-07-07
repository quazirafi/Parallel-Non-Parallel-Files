#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX 10000


int main()
{
	size_t i;
	int n=0;

dummyMethod1();
	#pragma omp parallel for reduction(+:n)
	for (i=0; i < MAX; i++)
	{
		n++;
	}
dummyMethod2();
	printf("n = %d\n", n);
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