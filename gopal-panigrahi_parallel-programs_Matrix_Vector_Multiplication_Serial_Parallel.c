/*
  Author : Gopal Panigrahi
  Date : 5 September 2020
  Description : A large martix and a vector are multiplied parallely.
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
  long size = 10000;

  /*
    Create and initializes large matrix and vector for multiplication
  */
  int **matrix = (int**)malloc(size*sizeof(int*));
dummyMethod3();
  for(long i=0;i<size;i++){
    matrix[i] = (int*)malloc(size*sizeof(int));
  }
dummyMethod4();

  int *vector = (int*)malloc(size*sizeof(int));
  int *result = (int*)calloc(size,sizeof(int));

dummyMethod3();
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      matrix[i][j] = i+j;
    }
    vector[i] = i;
  }
dummyMethod4();

  // SERIAL REGION
  double start = omp_get_wtime();
			dummyMethod3();
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      result[i] += matrix[i][j]*vector[j];
    }
  }
			dummyMethod4();
  double end = omp_get_wtime();
  printf("Time Taken In Serial %lf \n",end-start);

  // PARALLEL REGION
  start = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for default(none) collapse(2) shared(matrix,vector,result,size) schedule(auto)
  for(long i=0;i<size;i++){
    for(long j=0;j<size;j++){
      result[i] += matrix[i][j]*vector[j];
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