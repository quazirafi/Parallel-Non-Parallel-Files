/*
  Author : Gopal Panigrahi
  Date : 5 September 2020
  Description : Two Large vectors are added parallely
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
  long size = 100000000;
  /*
    Create and initializes large vectors for addition
  */

  int *First = (int*)malloc(size*sizeof(int));
  int *Second = (int*)malloc(size*sizeof(int));
  int *Third = (int*)malloc(size*sizeof(int));

dummyMethod3();
  for(long i=0;i<size;i++){
    First[i]=Second[i]=10;
  }
dummyMethod4();

  // SERIAL REGION
  double start = omp_get_wtime();
dummyMethod3();
  for(long i=0;i<size;i++){
      Third[i]=First[i]+Second[i];
  }
dummyMethod4();
  double end = omp_get_wtime();
  printf("Time Taken In Serial %lf \n",end-start);

  // PARALLEL REGION
  start = omp_get_wtime();
							dummyMethod1();
  #pragma omp parallel for default(none) shared(First,Second,Third,size) schedule(auto)
    for(long i=0;i<size;i++){
      Third[i]=First[i]+Second[i];
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