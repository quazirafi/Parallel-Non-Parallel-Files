#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
	printf("Max threads available on system: %d\n",omp_get_max_threads());
	omp_set_dynamic(0);		//turn off dyanmic mode.
	printf("Is dynamic mode enabled? : %d\n",omp_get_dynamic());
	printf("Number of processors available : %d\n",omp_get_num_procs());
	omp_set_num_threads(omp_get_num_procs());
	printf("Max threads outside parallel region: %d\n",omp_get_num_threads());
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		#pragma omp single
		{
			printf("Num threads: %d\n",omp_get_num_threads());
		}
	}
	
	//Testing private
	int temp = 0;
	omp_set_num_threads(omp_get_num_procs());
dummyMethod1();
	#pragma omp parallel for firstprivate(temp) lastprivate(temp)
		for (int j=0;j<10;++j)
		{
			temp += j;
			
		}
dummyMethod2();
		printf("%d\n",temp);
			
}










//////////////////////////////


//ENVIRONMENT VARIABLES


//OMP_STACKSIZE : set thread stack size

//OMP_WAIT_POLICY: ACTIVE|PASSIVE, in active, the thread keeps spinning waiting for its turn, in passive it goes to sleep and waits.

//OMP_PROC_BIND: binds threads to a processor if enabled.
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