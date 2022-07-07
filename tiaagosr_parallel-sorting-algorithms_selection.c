#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void selection_sort(int *, unsigned long, int numThreads);
void imprimir_vetor(int *, unsigned long);

int main(int argc, char *argv[])
{
  struct timeval timevalA;
        struct timeval timevalB;

  int *vetor = NULL, numThreads;
  unsigned long tam, i = 0;

  if (argc != 3) {
    printf("Necessita de 2 elementos\n");
    exit(EXIT_FAILURE);
  }

  tam = atoi(argv[1]);
  numThreads = atoi(argv[2]);
  
  if(!(numThreads > 0)){
		printf("Número de threads deve ser > 0\n");
		exit(EXIT_FAILURE);
	}

  if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
    printf("Erro ao alocar memória\n");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
			dummyMethod3();
  for (i = 0; i < tam; i++) {
    *(vetor + i) = random() % 10000;
  }
			dummyMethod4();

  gettimeofday(&timevalA, NULL);
  selection_sort(vetor, tam, numThreads);
  gettimeofday(&timevalB, NULL);

  printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

  //imprimir_vetor(vetor, tam);

  free(vetor);
  return EXIT_SUCCESS;
}

void selection_sort(int *vetor, unsigned long tam, int numThreads)
{
  unsigned long i, j, min;
  int aux;

  for (i = 0; i < tam - 1; i++) {
    min = i;
							dummyMethod1();
    #pragma omp parallel for schedule(static) num_threads(numThreads) shared(vetor, i, min) private(j)
    for (j = i+1; j < tam; j++) {
      if (vetor[j] < vetor[min]) {
        min = j;
      }
    }
							dummyMethod2();
    if (vetor[i] != vetor[min]) {
      aux = vetor[i];
      vetor[i] = vetor[min];
      vetor[min] = aux;
    }
  }
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
  unsigned long i;
  for (i = 0; i < tam; i++) {
    printf("%d\t ", vetor[i]);
  }
  printf("\n");
}


int validador(int *vetor, unsigned long tam)
{
  unsigned long i;
  for (i = 0; i < tam - 1; i++) {
    if (vetor[i] > vetor[i + 1]) {
      return 0;
    }
  }
  return 1;
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