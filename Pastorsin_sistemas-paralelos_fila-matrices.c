#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Time in seconds from some point in the past */
double dwalltime();


int main(int argc, char*argv[]) {
  double *A, *B, *C;
  int i, j, k, N;
  int check = 1;
  double timetick;

//Controla los argumentos al programa
  if (argc < 3) {
    printf("\n Faltan argumentos:: N dimension de la matriz, T cantidad de threads \n");
    return 0;
  }
  N = atoi(argv[1]);
  int numThreads = atoi(argv[2]);
  omp_set_num_threads(numThreads);


//Aloca memoria para las matrices
  A = (double*)malloc(sizeof(double) * N * N);
  B = (double*)malloc(sizeof(double) * N * N);
  C = (double*)malloc(sizeof(double) * N * N);

//Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i * N + j] = 1;
      B[i + j * N] = 1;
    }
  }
			dummyMethod4();

  timetick = dwalltime();
//Realiza la multiplicacion
			dummyMethod1();
  #pragma omp parallel for shared(A, B, C, N) private(i, j, k)
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      C[i * N + j] = 0;
      for (k = 0; k < N; k++) {
        C[i * N + j] = C[i * N + j] + A[i * N + k] * B[k + j * N];
      }
    }
  }
			dummyMethod2();
  printf("Tiempo en segundos %f \n", dwalltime() - timetick);

//Verifica el resultado
			dummyMethod3();
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      check = check && (C[i * N + j] == N);
    }
  }
			dummyMethod4();

  if (check) {
    printf("Multiplicacion de matrices resultado correcto\n");
  } else {
    printf("Multiplicacion de matrices resultado erroneo\n");
  }

  free(A);
  free(B);
  free(C);
  return (0);
}



/*****************************************************************/

#include <sys/time.h>

double dwalltime()
{
  double sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  sec = tv.tv_sec + tv.tv_usec / 1000000.0;
  return sec;
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