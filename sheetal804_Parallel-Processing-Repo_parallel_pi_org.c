#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int i,th_id,num_thd;
	double x,sum=0.0,num_step,step,pi;
	scanf("%lf",&num_step);
	//#pragma omp parallel 
	{
		th_id = omp_get_thread_num();
		num_thd=omp_get_num_threads();
		printf("\n NUm of threads:%d",num_thd);
		step=1.0/(double)num_step;   //h
dummyMethod1();
		#pragma omp parallel for shared(sum,x) private(i,th_id) reduction(+:sum)
		for(i=0,th_id=0;i<num_thd;i++,th_id++)
		{
			
				
				//#pragma omp for 
				for(i=1;i<=num_step/num_thd;i++)
				{
			
					x=(i-.5)*step;
					sum+=(4/(1.0+x*x));
					printf("\n sum %d:%lf\tID:%d",i,sum,th_id);
				}
			}
		
		pi=step*sum;
dummyMethod2();
		printf("pi:%lf",pi);
	
	}	
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