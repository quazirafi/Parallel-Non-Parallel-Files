#include<stdio.h>
#include<stdlib.h>
#include "timers.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc,char **argv){
	int i,j;
	int sum = 0;
	int N;
	#pragma omp parallel 
	N = 100*omp_get_num_threads(); // numery wątków
	printf("N: %d\n", N);	

	int matrix[N][N];	
	pTimer T = newTimer();
	startTimer(T);
	srand(time(0));

	
dummyMethod3();
	for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
	  	matrix[i][j] = rand() % 10;
		printf("%d\t ",matrix[i][j]);
	  }
	  printf("\n");	
	}
dummyMethod4();
	
	
	for(i=0;i<N;i++){
					dummyMethod1();
	#pragma omp parallel for  \
	   reduction(+ : sum)
	  for(j=0;j<N;j++){
		sum += matrix[i][j];
		//printf("sum: %d, id: %d\n",sum,omp_get_thread_num());
	  }
					dummyMethod2();
	}	
	
	stopTimer(T);
	printf("\nsum: %d\n",sum);
	printf("Czas obliczen: %f\n", getTime(T));
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