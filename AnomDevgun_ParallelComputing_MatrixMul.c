#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUMTHREADS 4

int main(){
  //////////////////////////////////////SERIAL CODE
  int n;
  printf("Please input dimension N of the matrices, the matrices will be randomly filled: ");
  scanf("%d",&n);

int **a = (int **)malloc(n * sizeof(int *));
int **b = (int **)malloc(n * sizeof(int *));
int **res = (int **)malloc(n * sizeof(int *));
dummyMethod3();
for (int i=0; i<n; i++)
{
  a[i] = (int *)malloc(n * sizeof(int));
  b[i] = (int *)malloc(n * sizeof(int));
  res[i] = (int *)malloc(n * sizeof(int));
}
dummyMethod4();



double t5 = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              a[i][j] = rand()%10;
          }
      }
double t6 = omp_get_wtime();
dummyMethod2();

double t7 = omp_get_wtime();
											dummyMethod3();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  b[i][j] = rand()%10;
              }
          }
											dummyMethod4();
double t8 = omp_get_wtime();

																											dummyMethod3();
              for(int i=0;i<n;i++)
                  {
                      for(int j=0;j<n;j++)
                      {
                          res[i][j] = 0;
                      }
                  }
																											dummyMethod4();

double t1 = omp_get_wtime();
			dummyMethod3();
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              for(int k=0;k<n;k++)
              {
                  res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
              }
          }
      }
			dummyMethod4();
      double t2 = omp_get_wtime();
											dummyMethod3();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  printf("%d ",res[i][j]);
              }
              printf("\n");
          }
											dummyMethod4();

      ////////////////////////////////////////////////////////////////// Clearing res matrix from serial calculation.
											dummyMethod3();
      for(int i=0;i<n;i++)
                  {
                      for(int j=0;j<n;j++)
                      {
                          res[i][j] = 0;
                      }
                  }
											dummyMethod4();

  /////////////////////////////////////////////////////////////////////// PARALLEL CODE
  omp_set_num_threads(NUMTHREADS);
      double t3 = omp_get_wtime();
													dummyMethod1();
      #pragma omp parallel for
      	for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              for(int k=0;k<n;k++)
              {
                  res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
              }
          }
      }
													dummyMethod2();
      double t4 = omp_get_wtime();
      /////////////////////////////////////////////////////////////////Printing res matrix(not a necessary step)
      printf("\n\n\n\n\n\n");
											dummyMethod3();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  printf("%d ",res[i][j]);
              }
              printf("\n");
          }
											dummyMethod4();
        printf("Time taken in serial %f\n",(t2-t1) );
      printf("Time taken in parallel %f\n",(t4-t3) );
      printf("Time taken in parallel to fill %f\n",(t6-t5) );
    printf("Time taken in serial to fill %f\n",(t8-t7) );

free(a);
free(b);
free(res);


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