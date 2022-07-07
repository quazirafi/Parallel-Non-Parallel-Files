// RankSort (Enumeration Sort) Paralelo em OpenMP
// Entrada: vetor de ate 10^8 numeros distintos
// Saida: vetor ordenado
// Ultima revisão 10/12/2016

// Algoritmo
// 1. A thread master le a entrada.
// 2. Cada thread calcula uma parcela dos ranques.
// 3. Cada thread monta uma parte do vetor ordenado
// usando os ranques anteriormente calculados.

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 4
#define MAX_TAM 100000000

void imprime_vetor(double *v, int tam){
  int i;
  printf("[");
dummyMethod3();
  for(i = 0; i < tam; i++){
    printf("%g", v[i]);
    if(i != tam-1)
    	printf(", ");
  }
dummyMethod4();
  printf("]\n");
}

int main (int argc, char *argv[]){

  int n, i, j;
  int *ranques;
  double *a, *b;
  double tempo_inicial, tempo_final;

  omp_set_num_threads(NUM_THREADS);

  a = (double*) malloc(MAX_TAM * sizeof(double));

  n = 0;
  while(scanf("%lf", &a[n]) != EOF)
    n++;

  b = (double*) malloc(n * sizeof(double));
  ranques = (int*) malloc(n * sizeof(int));

  #ifdef DEBUG_FLAG
  printf("Vetor original: "); imprime_vetor(a, n);
  #endif

  tempo_inicial = omp_get_wtime();

  /* Cada thread calcula uma parcela dos ranques */
			dummyMethod1();
  #pragma omp parallel for \
          shared(a, ranques, n) \
          private(i, j) \
          default(none)
  for(i = 0; i < n; i++){
    ranques[i] = 0;
    for(j = 0; j < n; j++){
      if(a[j] < a[i])
        ranques[i]++;
    }
  }
			dummyMethod2();

  /* As threads montam o vetor b utilizando os */
  /* ranques previamente calculados.           */
			dummyMethod1();
  #pragma omp parallel for \
          shared(a, b, ranques, n) \
          private(i) \
          default(none)
  for(i = 0; i < n; i++){
    b[ranques[i]] = a[i];
  }
			dummyMethod2();

  #ifdef DEBUG_FLAG
  printf("Vetor ordenado: "); imprime_vetor(b, n);
  #endif

  tempo_final = omp_get_wtime();
	
  #ifdef STATS_FLAG
  printf("%f\t", tempo_final-tempo_inicial);
  #else
			dummyMethod3();
  for(i = 0; i < n; i++)
    printf("%g\n", b[i]);
			dummyMethod4();
  #endif

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