#include "stdio.h"
#include "stdlib.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main() {
  int m, n, p, q;
  double sum = 0;
  m = 1000;
  n = p = 1000;
  q = 1000;
  
	double **first = malloc(m * sizeof(double *));
dummyMethod3();
  for(int i = 0; i < m; i++) {
    first[i] = malloc(n * sizeof(double));
  }
dummyMethod4();
  double **second = malloc(p * sizeof(double *));
dummyMethod3();
  for(int i = 0; i < p; i++) {
    second[i] = malloc(q * sizeof(double));
  }
dummyMethod4();
  double **multiply = malloc(m * sizeof(double *));
dummyMethod3();
  for(int i = 0; i < m; i++) {
    multiply[i] = malloc(q * sizeof(double));
  }
dummyMethod4();
  
  srand(time(0));
dummyMethod3();
  for (int i = 0; i < m; i++){
	  for (int j = 0; j < n; j++){
      first[i][j] = (rand() % 255);
      
    }
  }
dummyMethod4();

			dummyMethod3();
  for (int i = 0; i < p; i++){
	  for (int j = 0; j < q; j++){
      second[i][j] = (rand() % 255);
    }
  }
			dummyMethod4();

  double start_time, run_time;
  start_time = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for
  for (int c = 0; c < m; c++) {
    for (int d = 0; d < q; d++) {
      for (int k = 0; k < p; k++) {
        sum = sum + first[c][k]*second[k][d];
      }
      multiply[c][d] = sum;
      sum = 0;
    }
  }
			dummyMethod2();
  run_time = omp_get_wtime() - start_time;
  printf("Run Time: %f \n", run_time);

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