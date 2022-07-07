#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	int num_of_iter;
	float result = 0;
	int i = 1;

	scanf("%d", &num_of_iter);
dummyMethod1();
	#pragma omp parallel for
	for( i = 1; i <= num_of_iter; i++)
		result += 1.0/i;
	printf("%f\nThe number of terms:%d\n", result, num_of_iter);
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