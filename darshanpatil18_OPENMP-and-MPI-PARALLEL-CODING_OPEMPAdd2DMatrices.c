/*
Addition of two 2D matrices and finding of execution time
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define row 2

int A[row][row];
int B[row][row];
int C[row][row];

int main() 
{
    int i,j,k;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
    omp_set_num_threads(omp_get_num_procs());
dummyMethod3();
    for (i= 0; i< row; i++)
        for (j= 0; j< row; j++)
	{
		printf("Enter a Number for 'A' Matrix for the Row and Column : ");
dummyMethod4();
		scanf("%d", &A[i][j]);
    	printf("Enter a Number for 'B' Matrix for the Row and Column : ");
		scanf("%d", &B[i][j]);
       	}
    gettimeofday(&tv1, &tz);
							dummyMethod1();
    #pragma omp parallel for private(i,j) shared(A,B,C)
    for (i = 0; i < row; ++i) {
        for (j = 0; j < row; ++j) {
                C[i][j] = A[i][j] + B[i][j];
        }
    }
							dummyMethod2();

	printf("The Matrix after Addition is : \n");
	dummyMethod3();
	for (i = 0; i < row; ++i) {
        for (j = 0; j < row; ++j) {
                printf("%d ", C[i][j]);
        }
        printf("\n");
    }
	dummyMethod4();
	
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Execution Time = %f Seconds \n", elapsed);
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