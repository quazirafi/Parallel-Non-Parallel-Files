#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAXITER 10000000

int fibonacci(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char** argv) {
	int i;
	double sum;
	
	sum = 0;
dummyMethod1();
        #pragma omp parallel for private(i) reduction(+:sum)
	for (i = 0; i < MAXITER; i++) {
		sum += fibonacci(i%20);
	}
dummyMethod2();
	printf("%.2lf\n", sum);
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