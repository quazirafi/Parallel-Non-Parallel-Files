#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

#define A_SIZE 10

int main(int argc , char* argv[]){
	int phase,size,i,tmp;
	int thread_count;
	thread_count = strtol(argv[1] , NULL , 10);	
	int array[A_SIZE] = {12,34,23,51,6,7,90,25,66,89};
	size = A_SIZE;
	/*starting to sort*/	
	for(phase = 0 ; phase < size; phase++){
		if(phase%2 == 0){
dummyMethod1();
			#pragma omp parallel for num_threads(thread_count) default(none) shared(array,size) private(i , tmp)
			for(i = 1 ;i<size ; i+=2){
				if(array[i-1] > array[i]){
					tmp = array[i-1];
					array[i-1] = array[i];
					array[i] = tmp;
				}
			} 
dummyMethod2();
		}
		else{
					dummyMethod1();
			#pragma omp parallel for num_threads(thread_count) default(none) shared(array,size) private(i,tmp)
			for(i=1;i<size-1;i+=2){
				if(array[i] > array[i+1]){
					tmp = array[i+1];
					array[i+1] = array[i];
					array[i] = tmp;
				}
			}
					dummyMethod2();
		}
	}
	/* Print Result */
	for(i=0;i<A_SIZE;i++){
		printf("%d ", array[i] );
	}
	
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