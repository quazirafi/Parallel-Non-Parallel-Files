#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 2000

int main(int argc, char **argv){
  int nb, i , j, k;
  double t,start,stop;
  double* matrice_A;
  double* matrice_B;
  double* matrice_res;

  // Allocations
  matrice_A = (double*) malloc(SIZE*SIZE*sizeof(double)) ;
  matrice_B = (double*) malloc(SIZE*SIZE*sizeof(double)) ;
  matrice_res = (double*) malloc(SIZE*SIZE*sizeof(double)) ;

  // Initialisations
dummyMethod3();
  for(i = 0; i < SIZE; i++){
    for(j = 0; j < SIZE; j++){
      matrice_A[i*SIZE + j] = (double)rand()/(double)RAND_MAX;
      matrice_B[i*SIZE + j] = (double)rand()/(double)RAND_MAX;
    }
  }
dummyMethod4();

  // Calcul en faisant varier le nombre de threads
  printf("Nb.threads\tTps.\n");
  for(nb=1;nb<=8;nb++){
    start = omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for num_threads(nb) private(j,k)
    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
        matrice_res[i*SIZE + j] = 0.0;
        for(k = 0; k < SIZE; k++){
          matrice_res[i*SIZE + j] += (matrice_A[i*SIZE + k]*matrice_B[k*SIZE + j]);
        }
      }
    }
							dummyMethod2();
    stop=omp_get_wtime();
    t=stop-start;
    printf("%d\t%f\n",nb,t);
  }

  // Liberations
  free(matrice_A);
  free(matrice_B);
  free(matrice_res);
  return EXIT_SUCCESS;
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