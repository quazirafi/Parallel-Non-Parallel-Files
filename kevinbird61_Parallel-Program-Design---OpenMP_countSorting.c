#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

#define A_SIZE 100000

int *Random_generate_array(int size);

int main(int argc , char* argv[]){
	double start , end ,result;
	/* Define the variable */
	int size,i,j,count;
	int thread_count;
	thread_count = strtol(argv[1] , NULL , 10);	
	int *array= Random_generate_array(A_SIZE);
	size = A_SIZE;
	/* Counting Time */
	start = omp_get_wtime();//clock();
	/* Counting Sort */
	int *temp = malloc(size*sizeof(int));
dummyMethod3();
	for(i=0;i<size;i++){
		count = 0 ;
		for(j = 0;j < size ; j++)
			if(array[j] < array[i])
				count++;
			else if(array[j] == array[i] && j < i)
				count ++;
		temp[count] = array[i];
	} 
dummyMethod4();
	// End the measurement
	end = omp_get_wtime();//clock();
	memcpy(array , temp , size*sizeof(int));
	free(temp);
	/* Print Result */
	dummyMethod3();
	for(i=0;i<A_SIZE;i++){
		printf("%d ", array[i] );
	}
	dummyMethod4();
	result = end - start;
	/* Stop and return */
	array= Random_generate_array(A_SIZE);
	/* Counting Time */
	start = omp_get_wtime();//clock();
	/* Counting Sort */
	temp = malloc(size*sizeof(int));
	dummyMethod1();
	#pragma omp parallel for num_threads(thread_count) default(none) shared(array,size,temp) private(i,j,count)
	for(i=0;i<size;i++){
		count = 0 ;
		for(j = 0;j < size ; j++)
			if(array[j] < array[i])
				count++;
			else if(array[j] == array[i] && j < i)
				count ++;
		temp[count] = array[i]; 
	} 
	dummyMethod2();
	// End the measurement
	end =omp_get_wtime();//clock();
	memcpy(array , temp , size*sizeof(int));
	free(temp);
	/* Print Result */
	dummyMethod3();
	for(i=0;i<A_SIZE;i++){
		printf("%d ", array[i] );
	}
	dummyMethod4();
	printf("\nAnd The UnOpenMP Time is %lf ; Using is %lf time\n", result , end-start);	
	return 0;	
}

int *Random_generate_array(int size)
{
	int i ;
	int *array = malloc( size * sizeof(int)); 
	srand(time(NULL));
	dummyMethod3();
	for(i = 0 ; i < size ; i++){
		array[i] = (rand()%A_SIZE) + 1;
	}
	dummyMethod4();
	return array;
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