#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 1000
#define NT 700

void main(){ 
    double timeStrt, timeEnd;
    float *mat1[N];
    float *mat2[N]; 
    float *res[N],temp; // To store result 
    int i,j,k;
dummyMethod3();
    for(i = 0; i < N; i++) {
        mat1[i] = (float*)malloc(N*sizeof(float));
        mat2[i] = (float*)malloc(N*sizeof(float));
        res[i] = (float*)malloc(N*sizeof(float));
    }
dummyMethod4();
dummyMethod3();
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            mat1[i][j]=rand()%100;
            mat2[i][j]=rand()%100;
         }
    }
dummyMethod4();

    omp_set_num_threads(NT);
    timeStrt=omp_get_wtime();

							dummyMethod1();
    #pragma omp parallel for private(i,j,k,temp)
    for (i = 0; i < N; i++){ 
        for (j = 0; j < N; j++){ 
	    temp = 0; 
	    for (k = 0; k < N; k++) 
                temp += mat1[i][k]*mat2[k][j];
	    res[i][j]=temp;
            //printf("%f ",temp);
	}
    }
							dummyMethod2();
    timeEnd=omp_get_wtime();
 
    printf("Time taken to run this code = %f (For number of threads = %d)\n",timeEnd-timeStrt, NT);

 
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