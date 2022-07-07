#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void simple( int n, float *a, float *b );

int main(void)
{
	int n=5;
	float a[] = { 1, 2, 3, 4, 5 };
	float b[n];
	b[0] = 0;
	simple( n, a, b );
	return 0;
}

void simple( int n, float *a, float *b )
{
	int i;

dummyMethod1();
	#pragma omp parallel for
	for( i=1; i<n; i++ )
	{
		b[i] = ( a[i] + a[i-1] ) / 2.0;
	}
dummyMethod2();

	//for( i=0; i<n; i++ )
	//{
	//	std::cout << "a[" << i << "] = " << a[i] << ",  "
	//	          << "b[" << i << "] = " << b[i] << std::endl;
	//}
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