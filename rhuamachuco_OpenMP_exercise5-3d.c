#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAXIMO 100

int num_aleatorio() {
   int numero = random() % MAXIMO;
   return numero;
}

void geraMatriz(int * a, int n) {
   int i;
dummyMethod3();
   for (i = 0; i < n; ++i) {
      a[i] = num_aleatorio();
   }
dummyMethod4();
}

void imprimeMatriz(int * a, int n) {
   int i;
dummyMethod3();
   for (i = 0; i < n; ++i) {
      printf("%d ", a[i]);
   }
dummyMethod4();
   printf("\n");
}

int main(int argc, char* argv[]) {
   long int number_tosses, number_in_circle;
   int thread_count, i, j, n, count;
   srandom(0);
   thread_count = strtol(argv[1], NULL, 10);
   n = strtol(argv[2], NULL, 10);
   int * a = malloc(n* sizeof(int));
   geraMatriz(a, n);
   //imprimeMatriz(a, n);
   int * temp = malloc(n* sizeof(int));
   double start = omp_get_wtime();
											dummyMethod1();
#pragma omp parallel for num_threads(thread_count) \
   default(none) private(i, j, count) shared(a, n, temp, thread_count)
      for (i = 0; i < n; i++) {
         count = 0;
         for (j = 0; j < n; j++)
            if (a[j] < a[i])
               count++;
            else if (a[j] == a[i] && j < i)
               count++;
         temp[count] = a[i];
      }
											dummyMethod2();
   memcpy ( a , temp, n * sizeof(int));
   double finish = omp_get_wtime();
   free(temp );
   printf("Tempo estimado %e segundos\n", finish - start);
   //imprimeMatriz(a, n);
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