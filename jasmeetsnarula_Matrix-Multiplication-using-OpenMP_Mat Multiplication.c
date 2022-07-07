#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include "omp.h"
#include <time.h>
#include <math.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
 
int main(){
 
#define max_value 10
#define min_value 1
 
//Initializing Variables

int i, j, k,N,s,sum=0;
int num_threads =0;
double ParallelTime = 0, SequentialTime = 0;
 
 
//Input the values of matrix
            printf("Enter the Matrix dimension N (N x N): ");
            scanf("%d" , &N);
            printf("Enter the Size of the block the Matrix is divided: ");
            scanf("%d" , &s);
 
//Initialize all the matrix used for Matrix Multiplication and comparison

    int (*InputMatrix1)[N] = malloc(N * sizeof(*InputMatrix1));
    int (*InputMatrix2)[N] = malloc(N * sizeof(*InputMatrix2));
    //int (*OutputMatrixBlock)[N] = malloc(N * sizeof(*OutputMatrixBlock));
    int (*OutputMatrixPara)[N] = malloc(N * sizeof(*OutputMatrixPara));
    int (*OutputMatrixSeq)[N] = malloc(N * sizeof(*OutputMatrixSeq));
           
//Initializing the 2 Input Matrix by randomly generating values
 
// #pragma omp parallel for schedule (static)
																							dummyMethod3();
            for(i=0;i<N;i++){
                        for(j=0; j<N ;j++){
                                    InputMatrix1[i][j] = rand() % max_value + min_value;
                        }
            }
																							dummyMethod4();
                       
//  #pragma omp parallel for schedule (static)
																							dummyMethod3();
            for(i=0;i<N;i++){
                        for(j=0; j<N;j++){
                                    InputMatrix2[i][j] = rand() % max_value + min_value;
                        }
            }
																							dummyMethod4();
           
 
// Start of OMP_BLOCK Code  
//Execution in Parallel                  
struct timeval t0,t1;
gettimeofday(&t0, 0);

 
int i1=0,k1=0,j1=0;
dummyMethod1();
#pragma omp parallel for shared(InputMatrix1,InputMatrix2,OutputMatrixPara,N,s) private(i,j,k,i1,j1,k1,sum) schedule(auto) num_threads(4) collapse(2) // **OPEN_MP CODE To FOR OPTIMIZATION**
for (i=0; i<N; i+=s)
    for (j=0; j<N; j+=s)
      for (k=0; k<N; k+=s)
        for (i1=i;i1<i+s;i1++)
          for (j1=j;j1<j+s;j1++)
            {
              int sum=0;
              for (k1=k;k1<k+s;k1++)
                {
                  sum+=InputMatrix1[i1][k1]*InputMatrix2[k1][j1];
                }
              OutputMatrixPara[i1][j1]+=sum;
            }
dummyMethod2();
 
gettimeofday(&t1, 0);
ParallelTime = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
 
//Executing Matrix Sequentially  
 
double matrix_mult_serial(int N);
{
            int i,j,k;

																							dummyMethod3();
            for(i=0;i<N;i++)
            {
                        for(j=0;j<N;j++)
                        {
                                   
                                    OutputMatrixSeq[i][j] = 0.0;
                                   
 
                                    for(k=0;k<N;k++)
                                    {
                                                OutputMatrixSeq[i][j] +=  InputMatrix1[i][k]*InputMatrix2[k][j];
                                    }
                        }
            }
																							dummyMethod4();
           
            gettimeofday(&t1, 0);
            SequentialTime = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
           
           
}

//Print the Input and output Matrix
 
 
/*                   
            printf("Input Matrix 1 is : \n");
            for(int i=0;i<N;i++){
                        for(int j =0;j<N;j++){
                                    printf("%d      ",InputMatrix1[i][j]);
                        }
                        printf("\n");
            }
           
            printf("Input Matrix 2 : \n");
            for(int i=0;i<N;i++){
                        for(int j =0;j<N;j++){
                                    printf("%d      ",InputMatrix2[i][j]);
                        }
                        printf("\n");
            }
           
 
            printf("Output for Parallel : \n");
            for(int i=0;i<N;i++){
                        for(int j =0;j<N;j++){
                                    printf("%d      ",OutputMatrixPara[i][j]);
                        }
                        printf("\n");
            }       
 
            printf("Output for Sequential : \n");
            for(int i=0;i<N;i++){
                        for(int j =0;j<N;j++){
                                    printf("%d      ",OutputMatrixSeq[i][j]);
                        }
                        printf("\n");
            }
*/       
            printf("Elapsed time to execute Sequentially : %f \n ", SequentialTime);
            printf("Elapsed time taken to execute in Parallel: %f \n ", ParallelTime);
           
            return (0);
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