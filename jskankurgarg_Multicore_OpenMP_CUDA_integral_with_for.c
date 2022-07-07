#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
double f(double x){return x*x;}
void main(int argc,char*argv[]){
	 int tc=strtol(argv[1],NULL,10);
	 double a,b,area=0.0,h;
	 int n;
	 printf("enter a , b and n:\n");
	 scanf("%lf %lf %d",&a,&b,&n);
	 printf("\ntc=%d\n",tc);
	 h=(b-a)/n;
	 area=h*((f(a)+f(b))/2);
	 int i=0;
	 double start=0.0,end=0.0,sum=0.0,x;
	 double limit=(double)n/tc;
	 printf("\nhello\n");
dummyMethod1();
	 #pragma omp parallel for num_threads(tc) reduction(+:sum)
	 	for(i=1;i<n;i++)
		{
		  x=a+(i*h);
		  sum+=f(x);
		}
dummyMethod2();
	area+=h*sum;
	 printf("\ntotal area: %.10lf\n",area);
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