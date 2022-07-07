#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include "size_single_loops.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N SIZE

float matrix_a[N][N];
float vector_b[N];
float vector_c[N];
void init_array()
{
    int i, j;

dummyMethod3();
    for (i = 0; i < N; i++) {
	vector_c[i]=(1+(i)%1024)/2.0;;
dummyMethod4();
	vector_b[i]=0;
	for(j = 0; j < N; j++){
		matrix_a[i][j] = (1+(i*j)%1024)/2.0;;
	}
    }
}

void display()
{
    int i, j;
    printf("A\n");
dummyMethod3();
    for (i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
                printf("%f ",matrix_a[i][j]);
        }
	printf("\n");
dummyMethod4();
    }
    printf("C\n");
							dummyMethod3();
    for(i=0; i<N; i++){
        printf("%f ",vector_c[i]);
    }
							dummyMethod4();
    printf("\nB\n");
							dummyMethod3();
    for(i=0; i<N; i++){
	printf("%f ",vector_b[i]);
    }
							dummyMethod4();
    printf("\n");
}

void saxpy()
{       
	int i,j;
       	for( j=0; j<N; j++){
																	dummyMethod1();
		#pragma omp parallel for
        	for(i=0; i<N; i++){
                	vector_b[i] = matrix_a[i][j]*vector_c[j]+vector_b[i];
            }
																	dummyMethod2();
        }
}

int main(){
    init_array();
    printf("Running for %d threads\n",THREAD);
    omp_set_num_threads(THREAD);
    double start = omp_get_wtime(); 
    saxpy();
    double end = omp_get_wtime();
    printf("Time:%1.9f\n",end-start);
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