/*
Using OpenMP, Design, develop and run a multi-threaded program to perform and print vector addition.
*/
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define row 4

int A[row];
int B[row];
int Sum[row];

int main() 
{
    int i; 
    omp_set_num_threads(omp_get_num_procs());
    
	printf("Enter the Matrix 'A' : \n");
dummyMethod3();
	for (i= 0; i< row; i++){
		scanf("%d", &A[i]);
	}
dummyMethod4();
	
    printf("Enter the Matrix 'B' : \n");
dummyMethod3();
    for (i= 0; i< row; i++)
		scanf("%d", &B[i]);
dummyMethod4();
      
dummyMethod1();
	#pragma omp parallel for private(i) shared(A)
    for (i = 0; i < row; ++i) {    
        Sum[i] += A[i] + B[i];
    }
dummyMethod2();
	
	printf("The Sum Matrix is : \n");
	dummyMethod3();
	for (i= 0; i< row; i++)
		printf("%d\n",Sum[i]);
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