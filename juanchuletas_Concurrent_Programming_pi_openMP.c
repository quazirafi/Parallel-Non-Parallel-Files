#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define  n_steps 1000000


int main()
{
	int i;
	double step,pi,x,sum;


	step = 1.0/(double)n_steps;
	sum = 0.0;

dummyMethod1();
#pragma omp parallel for \
	private(x) reduction(+:sum)
	

	for(i=0;i<n_steps;i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0 + x*x);

	}
dummyMethod2();

	pi = step*sum;
	printf("Pi =%lf\n",pi);
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