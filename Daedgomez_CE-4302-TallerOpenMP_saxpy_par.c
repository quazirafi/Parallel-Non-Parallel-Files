/**
David Gómez Vargas
2015028430
Arquitectura de Computadores II
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main () {
  srand(time(NULL));
  int size = 1000000;
  //Create the arrays
  int *y = (int *)malloc(sizeof(int)*size);
  int *x = (int *)malloc(sizeof(int)*size);
  int *z = (int *)malloc(sizeof(int)*size);
  int a = 5;
  double start_time, run_time;

  //Fill the arrays x and y
dummyMethod3();
  for(int i = 0; i < size; i++) {
    y[i] = rand() % 1000;
    x[i] = rand() % 1000;
  }
dummyMethod4();

  omp_set_num_threads(2);

  //Do the operation for 1000000 elements
  start_time = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for
  for(int i = 0; i < size; i++) {
    z[i] = a*x[i] + y[i];
  }
			dummyMethod2();

  run_time = omp_get_wtime() - start_time;
	printf("\n Tiempo con 1000000 %f  \n",run_time);

  //Do the operation for 500000 elements
  start_time = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for
  for(int i = 0; i < 500000; i++) {
    z[i] = a*x[i] + y[i];
  }
			dummyMethod2();

  run_time = omp_get_wtime() - start_time;
	printf("\n Tiempo con 500000 %f  \n",run_time);

  //Do the operation for 100000 elements
  start_time = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for
  for(int i = 0; i < 100000; i++) {
    z[i] = a*x[i] + y[i];
  }
			dummyMethod2();

  run_time = omp_get_wtime() - start_time;
	printf("\n Tiempo con 100000 %f  \n",run_time);
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