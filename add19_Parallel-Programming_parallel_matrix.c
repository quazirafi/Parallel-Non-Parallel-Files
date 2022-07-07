#include<time.h>
#include "omp.h"
#include<stdlib.h>
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int n, m, i, j;
	printf("Enter the dimensions of the matrices:");
	scanf("%d", &n);

	int a[n][n], b[n][n], c[n][n];
	srand(time(NULL));

dummyMethod3();
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			a[i][j] = (rand()%10);
			b[i][j] = (rand()%10);
			c[i][j] = 0;
		}
	}
dummyMethod4();
    double start, stop;
    start = omp_get_wtime();
dummyMethod1();
	 #pragma omp parallel for private(m, j) num_threads(4) 
		
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				
				for(m=0; m<n; m++){
					c[i][j] = c[i][j] + a[i][m] * b[m][j];				
				}	
				printf("%d ", c[i][j]);		
			}
		}	
dummyMethod2();
    stop = omp_get_wtime();
    printf("Time elapsed: %f", stop - start);

	
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