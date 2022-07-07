/*
  Author : Gopal Panigrahi
  Date : 5 September 2020
  Description : Two Large matrices are multiplied parallely
*/
#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main()
{
  long size = 1000;

  /*
    Create and initializes large matrices for multiplication
  */
  int **first_matrix = (int**)malloc(size*sizeof(int*));
dummyMethod3();
  for(long i=0;i<size;i++){
    first_matrix[i] = (int*)malloc(size*sizeof(int));
  }
dummyMethod4();

  int **second_matrix = (int**)malloc(size*sizeof(int*));
dummyMethod3();
  for(long i=0;i<size;i++){
    second_matrix[i] = (int*)malloc(size*sizeof(int));
  }
dummyMethod4();

  int **result_matrix = (int**)malloc(size*sizeof(int*));
dummyMethod3();
  for(long i=0;i<size;i++){
    result_matrix[i] = (int*)calloc(size,sizeof(int));
  }
dummyMethod4();

			dummyMethod3();
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      first_matrix[i][j] = second_matrix[i][j] = 1;
    }
  }
			dummyMethod4();

  // SERIAL REGION
  double start = omp_get_wtime();
			dummyMethod3();
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      for(long k=0;k<size;k++){
        result_matrix[i][j] += first_matrix[i][k] + second_matrix[k][j];
      }
    }
  }
			dummyMethod4();
  double end = omp_get_wtime();
  printf("Time Taken In Serial %lf \n",end-start);

  // PARALLEL REGION
  start = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for default(none) collapse(3) shared(first_matrix,second_matrix,result_matrix,size) schedule(auto)
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      for(long k=0;k<size;k++){
        result_matrix[i][j] += first_matrix[i][k] + second_matrix[k][j];
      }
    }
  }
			dummyMethod2();
  end = omp_get_wtime();
  printf("Time Taken In Parallel %lf \n",end-start);
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