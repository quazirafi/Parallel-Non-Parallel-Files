#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){

	static long num_steps = 300000;
	double  pi=0.0;

	double step = 1.0/(double)num_steps;

	double s_time=omp_get_wtime();

	printf("Serial code Start:%lf\n",s_time) ;
	
		double x, sum = 0.0;
		
dummyMethod3();
		for( int i=0; i<num_steps;i++){
			
			x=(0.5+i)*step;
			sum+=4.0/(1.0+x*x);
		
		}
dummyMethod4();
		
		pi=sum*step;

	double e_time=omp_get_wtime();	

	printf("\nSerial code End:%lf",e_time) ;
	printf("\nSerially Execution Time:%lf",e_time-s_time) ;
	 
	
	printf("\nSerially Calculated pi value:%lf\n",pi);
	


	pi=0.0;

	s_time=omp_get_wtime();
	printf("\nParallel code Start:%lf",s_time);

	dummyMethod1();
	#pragma omp parallel for reduction(+:pi)
	
	for(int i=0; i<num_steps;i++){
			
		double x=(0.5+i)*step;
		pi+=4.0/(1.0+x*x);
		
	}
	dummyMethod2();

	e_time=omp_get_wtime();

	printf("\nParallel code End:%lf",e_time) ;
	printf("\nParallel Execution Time:%lf",e_time-s_time) ;

	printf("\nParallelly Calculated pi value:%lf\n",pi*step);
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