#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "util.h"

int *matrix_multiplication(int *matrix1, size_t rows1, size_t columns1, int *matrix2, size_t rows2, size_t columns2){
  int *result = create_matrix(rows1, columns2);
  int sum = 0;
  int i, j, k;
  for(i=0; i<rows1; ++i){
    for(j=0; j<columns2; ++j){
dummyMethod1();
      #pragma omp parallel for reduction(+: sum)
      for(k=0; k<rows2; ++k){
	sum = sum + matrix1[i*columns1+k] * matrix2[k*columns2+j];
dummyMethod2();
      }
      result[i*columns1+j] = sum;
      sum = 0;
    }
  }

  return result;
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2 && argc != 3){
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  int *matrix1;
  int *matrix2;
  int *result_matrix;
  double begin, end;

  matrix2 = create_matrix(N, N);
  matrix1 = create_matrix(N, N);
  result_matrix = create_matrix(N, N);

  // Initialise matrices
  int i;
  srand48(time(NULL));
  for(i=0; i<N*N; ++i){
    matrix1[i] = lrand48() % RANGE_MAX;
    matrix2[i] = lrand48() % RANGE_MAX;
  }

  // Print Matrix for matrix multiplication
  if(argc == 3){
      printf("Matrices for matrix multiplication:\n");
      print_matrix(matrix1, N, N);
      print_matrix(matrix2, N, N);
  }

  // Measure time 
  begin = omp_get_wtime();
  
  result_matrix = matrix_multiplication(matrix1, N, N, matrix2, N, N);

  // Print result And give time
  end = omp_get_wtime();
  printf("Time spent: %fs\n", end-begin);
  if(argc == 3) {
    printf("\nResult matrix:\n");
    print_matrix(result_matrix, N, N);
  }

  // Free memory
  free(matrix1);
  free(matrix2);
  free(result_matrix);
  
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