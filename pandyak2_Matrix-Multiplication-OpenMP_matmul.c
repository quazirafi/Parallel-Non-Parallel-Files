#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define max_val 10
#define min_val 1
int main(){
int  numThreads, i, j, k,N,s;
printf("Enter the dimension for an N*N matrix: "); 
scanf("%d" , &N);
printf("Input the block-size of Matrix: ");
scanf("%d" , &s);
int (*dim_A)[N] = malloc(N * sizeof(*dim_A));
int (*dim_B)[N] = malloc(N * sizeof(*dim_B));
int (*dim_C)[N] = malloc(N * sizeof(*dim_C));
double timetaken = 0;
dummyMethod3();
		for(i=0;i<N;i++){
			for(j=0; j<N ;j++){
				dim_A[i][j] = rand() % max_val + min_val;
					  }
				}
		for(i=0;i<N;i++){
dummyMethod4();
dummyMethod3();
			for(j=0; j<N;j++){
				dim_B[i][j] = rand() % max_val + min_val;
			}
		}
dummyMethod4();
int result;
int num_threads =0;
struct timeval start, end;
gettimeofday(&start, 0);
int l,k1,m,sum;
dummyMethod1();
#pragma omp parallel for num_threads(2)
for (i=0; i<N; i+=s)
    for (j=0; j<N; j+=s)
      for (k=0; k<N; k+=s)
        for (l=i;l<i+s;l++)
          for (m=j;m<j+s;m++)
            {
              int sum=0; 
#pragma omp parallel for shared(dim_A,dim_B,dim_C) schedule(guided)
              for (k1=k;k1<k+s;k1++)
                {
                  sum+=dim_A[l][k1]*dim_B[k1][m];
                }
              dim_C[l][m]+=sum;
            }
dummyMethod2();
gettimeofday(&end, 0);
timetaken = (end.tv_sec-start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
printf("Elapsed time is : %f \n ", timetaken);
return(0);

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