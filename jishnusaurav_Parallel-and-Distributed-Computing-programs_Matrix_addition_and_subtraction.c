#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
int main () 
{
    int a[2][2]={0,1,2,3};
     int b[2][2]={5,6,7,8};
    int sum[2][2];
        int diff[2][2];
    int i;
 #pragma omp parallel sections
		{
		#pragma omp section
	   #pragma omp parallel for schedule(static,2)
dummyMethod3();
		for (i=0; i < 2; i++) 
		{
	   #pragma omp parallel for schedule(static,2)
		for (int j=0; j < 2; j++) {
dummyMethod4();
		sum[i][j] = a[i][j] + b[i][j]; 
			}
		}
	#pragma omp section
	   #pragma omp parallel for schedule(static,2)
dummyMethod3();
		for (i=0; i < 2; i++) 
		{
	   #pragma omp parallel for schedule(static,2)
		for (int j=0; j < 2; j++) {
dummyMethod4();
		diff[i][j] = a[i][j] - b[i][j]; 
			}
		}
}
printf("Matrix addition\n");
for (int l=0; l < 2; l++) {
dummyMethod3();
for (int k=0; k < 2; k++) {
		printf("%d  ",sum[l][k]);
			}
dummyMethod4();
		printf("\n");
			}
		
	    
printf("Matrix subtraction\n");
for (int l=0; l < 2; l++) {
dummyMethod3();
for (int k=0; k < 2; k++) {
		printf("%d  ",diff[l][k]);
			}
dummyMethod4();
		printf("\n");
			}
		
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