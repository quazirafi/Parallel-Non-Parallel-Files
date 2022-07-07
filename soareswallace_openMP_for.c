#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
	int i, j, k, thread_id;
	int a[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	int b[4][4] = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	int c[4][4] = {0};
dummyMethod1();
	#pragma omp parallel for private (j, k) num_threads(4)
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for (k=0;k<4;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
			int test;
			test++;
			thread_id = omp_get_thread_num();
			printf("teste: %d thread_id %d calculou c[%d][%d] = %d\n",test, thread_id, i, j, c[i][j]);
		}
	}
dummyMethod2();
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