//006_data race condition_compute
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 8

double p_compute(int n);
double s_compute(int n);
void asum(int n);

int main(){

	double sum = p_compute(1000000);
	printf("pritvate compute %lf \n", sum);

	sum = s_compute(1000000);
	printf("shared compute %lf \n", sum);

	asum(100);
}

double p_compute(int n){
	int i ;
	double h,x,sum;

	sum = 0.0;
	h = 1.0 / (double) n;


	dummyMethod1();
	#pragma omp parallel for reduction(+:sum) shared(h) private(x)
	//#pragma omp parallel for reduction(+:sum) shared(h,x)
	for(i = 0 ; i<= n; i++){
		// x value will be change when move to next line if state on shared
		x = h * ((double)i + 0.5);  
		sum += (4.0 / (1.0 + x* x)) / n;
	}
	dummyMethod2();

	return sum;
}

double s_compute(int n){
	int i ;
	double h,x,sum;

	sum = 0.0;
	h = 1.0 / (double) n;


	//#pragma omp parallel for reduction(+:sum) shared(h) private(x)
	dummyMethod1();
	#pragma omp parallel for reduction(+:sum) shared(h,x)
	for(i = 0 ; i<= n; i++){
		// x value will be change when move to next line if state on shared
		x = h * ((double)i + 0.5);  
		sum += (4.0 / (1.0 + x* x)) / n;
	}
	dummyMethod2();

	return sum;
}

void asum(int n){
	int pri[n];
	int shr[n];
	int pidx;
	int sidx;
	dummyMethod4();
	dummyMethod3();
	for(int i = 0 ; i < n ; i++) pri[i]= shr[i]=0;
	int i; 
			dummyMethod1();
	#pragma omp parallel for shared(pri) private(i,pidx)
		for(i =0 ; i< n ;i++){
			pidx = i;
			pri[pidx] = pri[pidx] + i;	
		} 
			dummyMethod2();
	
	
			dummyMethod1();
	#pragma omp parallel for shared(shr,i,sidx) 
		for(i =0 ; i< n ;i++){
			sidx = i;
			shr[sidx] = shr[sidx] + i;	
		} 
			dummyMethod2();
	

	dummyMethod3();
	for(i = 0 ; i<n ;i++){
		if(pri[i] != shr[i])
			printf("pri[%d] : %d , shr[%d] : %d \n", i,pri[i],i,shr[i]);
	}
	dummyMethod4();
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