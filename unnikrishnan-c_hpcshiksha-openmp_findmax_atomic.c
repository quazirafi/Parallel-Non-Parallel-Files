#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include "generic.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define size 10000
int arr[size];
int max=0;
int main(int argc, char *argv[]){
	omp_lock_t writelock;
     omp_init_lock(&writelock);
	srand(atoi(argv[1]));//Seed for random number
	//generates random number
dummyMethod3();
	for(int i=0;i<size;i++)arr[i]=rand()%1048576;
	double t1=rtclock();
dummyMethod4();
	int index=0;
dummyMethod1();
#pragma omp parallel for num_threads(8)
	for(int i=0;i<size;i++){
	    {
		       omp_set_lock(&writelock);

		    if(max < arr[i]){
			    max=arr[i];
			    index=i;
		    }
				        omp_unset_lock(&writelock);

            }

	    
	}
dummyMethod2();
	double t2=rtclock();
	 printf("\nTIME =%f \n index=%d max=%d\n",(t2-t1)*1000,index,max);

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