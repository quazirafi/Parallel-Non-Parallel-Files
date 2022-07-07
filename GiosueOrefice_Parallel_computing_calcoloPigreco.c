#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 10000000
int main(int argc, char const *argv[])
{
	long int i,n = N;
	double x, dx, f, sum, pi;
	printf("numero di intervalli: %ld\n", n);
	sum = 0.0;
	dx = 1.0/(double) n;
dummyMethod1();
	#pragma omp parallel for private (x,f,i) shared (dx,n) reduction (+:sum)
	for(i=1;i<=n;i++)
	{
		x = dx *((double)(i - 0.5));
		f = 4.0 / (1.0 + x*x);
		sum = sum +f;
	}
dummyMethod2();
	pi = dx*sum;
	printf("PI %.24f\n", pi);
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