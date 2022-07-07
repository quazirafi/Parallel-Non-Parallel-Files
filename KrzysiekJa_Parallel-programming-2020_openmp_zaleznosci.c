#include<stdlib.h>
#include<stdio.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000000





int main(){

  int i;
  double* A = malloc((N+2)*sizeof(double));
  double* B = malloc((N+2)*sizeof(double));
  double* C = malloc((N+2)*sizeof(double));
  double suma;

dummyMethod3();
  for(i=0;i<N+2;i++) A[i] = (double)i/N;
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;
dummyMethod4();
dummyMethod3();




  double t1 = omp_get_wtime();
dummyMethod4();
dummyMethod3();
  for(i=0; i<N; i++){
    A[i] += A[i+2] + sin(B[i]);
  }
dummyMethod4();
  t1 = omp_get_wtime() - t1;

  suma = 0.0;
dummyMethod3();
  for(i=0;i<N+2;i++) suma+=A[i];
  printf("suma %lf, czas obliczen %lf\n", suma, t1);
dummyMethod4();




			dummyMethod4();
			dummyMethod3();
  for(i=0;i<N+2;i++) A[i] = (double)i/N;
			dummyMethod4();
			dummyMethod3();
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;




  t1 = omp_get_wtime();

  omp_set_num_threads(10);
							dummyMethod1();
  #pragma omp parallel for
    for(i = 0; i < N; i++){
      C[i] += A[i] + A[i+2] + sin(B[i]);
    }
							dummyMethod2();

    t1 = omp_get_wtime() - t1;

  suma = 0.0;
							dummyMethod1();
  #pragma omp parallel for reduction(+ : suma)
    for(i = 0; i < N+2; i++) suma += C[i];
							dummyMethod2();
    printf("suma %lf, czas obliczen rownoleglych %lf\n", suma, t1);
  
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