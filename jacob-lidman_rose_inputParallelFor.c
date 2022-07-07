#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

static long num_steps=10000000;
double step;

int main()
{
  int i;
  double x,pi, sum=0.0;
  step=1.0/(double)num_steps;

dummyMethod1();
#pragma omp parallel for reduction (+:sum) private (x)
for(i=1;i<=num_steps;i++)
{
	x=(i-0.5)*step;
       	sum=sum+ 4.0/(1.0+x*x);
}
dummyMethod2();
 pi=step*sum;
 printf("step:%e sum:%f PI=%.20f\n",step,sum, pi);

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