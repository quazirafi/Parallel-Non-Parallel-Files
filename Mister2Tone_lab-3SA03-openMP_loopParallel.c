#include "omp.h"
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUMBER 500000
int main(int argc, char *argv[]){
	int i, data[NUMBER];
	int num_t,t_id;
	double result=0.0;
dummyMethod3();
	for(i=0;i<NUMBER;i++){
		data[i]=i*i;
	}
dummyMethod4();
	double start_time = omp_get_wtime();
dummyMethod1();
	#pragma omp parallel for 
	for(i=0;i<NUMBER;i++){
		num_t = omp_get_num_threads();
		t_id = omp_get_thread_num();
		result+=(sin(data[i])-cos(data[i]))/(sin(data[i]+cos(data[i])));
		//printf("t_id : %d/%d\n",t_id,num_t);
	}
dummyMethod2();
	double end_time = omp_get_wtime();
	double time = end_time - start_time;
	printf("Result = %f\n",result);
	printf("Time : %f\n",time);
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