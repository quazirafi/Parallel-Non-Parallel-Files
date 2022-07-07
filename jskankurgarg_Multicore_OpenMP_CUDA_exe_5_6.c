#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(int argc,char* argv[]){
	 if(argc!=2){
		  printf("Usage: ./a.out no_of_iterations\n");
		  exit(0);
	 }
	 int n=strtol(argv[1],NULL,10),i;
	 int flag=0;
	 /**error: schedule ‘runtime’ does not take a ‘chunk_size’ parameter*/
dummyMethod1();
	 #pragma omp parallel for schedule(runtime) firstprivate(flag)
	 for(i=0;i<n;i++)
		{
			 if(flag==0){
			 	printf("\nthread %d : iterations ",omp_get_thread_num());
			 }
			 printf("%d,",i);
			 flag=1;
	 	}
	 	printf("\n");
}
dummyMethod2();

/**
NOTE:export OMP_SCHEDULE=static,3
*/
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