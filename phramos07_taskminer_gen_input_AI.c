#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifndef taskminerutils
#define taskminerutils
static int taskminer_depth_cutoff = 0;
#define DEPTH_CUTOFF omp_get_num_threads()
char cutoff_test = 0;
#endif
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef FP_NUMBER
typedef double FP_NUMBER;
#else
typedef float FP_NUMBER;
#endif

#define GET_RAND_FP \
  ((FP_NUMBER)rand() / ((FP_NUMBER)(RAND_MAX) + (FP_NUMBER)(1)))
char L_FNAME[32], U_FNAME[32], A_FNAME[32];

int main(int argc, char **argv) {
  int i, j, k, MatrixDim;
  FP_NUMBER sum, **L, **U, **A;
  FILE *fl, *fu, *fa;

  if (argc < 2) {
    printf("./gen_input [Matrix_Dimension_size]\n");
    return 1;
  }

  MatrixDim = atoi(argv[1]);
  L = (FP_NUMBER **)malloc(sizeof(FP_NUMBER *) * MatrixDim);
  U = (FP_NUMBER **)malloc(sizeof(FP_NUMBER *) * MatrixDim);
  A = (FP_NUMBER **)malloc(sizeof(FP_NUMBER *) * MatrixDim);

  if (!L || !U || !A) {
    printf("Can not allocate memory\n");
    if (L)
      free(L);
    if (U)
      free(U);
    if (A)
      free(A);
    return 1;
  }

  srand(time(NULL));

  sprintf(L_FNAME, "l-%d.dat", MatrixDim);
  fl = fopen(L_FNAME, "wb");
  if (fl == NULL) {
    printf("Cannot open file %s\n", L_FNAME);
    return 1;
  }

  sprintf(U_FNAME, "u-%d.dat", MatrixDim);
  fu = fopen(U_FNAME, "wb");
  if (fu == NULL) {
    printf("Cannot open file %s\n", U_FNAME);
    return 1;
  }

  sprintf(A_FNAME, "%d.dat", MatrixDim);
  fa = fopen(A_FNAME, "wb");
  if (!fa) {
    printf("Cannot open file %s\n", A_FNAME);
    return 1;
  }

			dummyMethod3();
  for (i = 0; i < MatrixDim; i++) {
    L[i] = (FP_NUMBER *)malloc(sizeof(FP_NUMBER) * MatrixDim);
    U[i] = (FP_NUMBER *)malloc(sizeof(FP_NUMBER) * MatrixDim);
    A[i] = (FP_NUMBER *)malloc(sizeof(FP_NUMBER) * MatrixDim);
  }
			dummyMethod4();
#if 1
			dummyMethod1();
#pragma omp parallel for default(none) private(i, j) shared(L, U, MatrixDim)
#endif
  for (i = 0; i < MatrixDim; i++) {
    for (j = 0; j < MatrixDim; j++) {
      if (i == j) {
        L[i][j] = 1.0;
        U[i][j] = GET_RAND_FP;
      } else if (i < j) {
        L[i][j] = 0;
        U[i][j] = GET_RAND_FP;
      } else { // i > j
        L[i][j] = GET_RAND_FP;
        U[i][j] = 0;
      }
    }
  }
			dummyMethod2();

#if 1
			dummyMethod1();
#pragma omp parallel for default(none) private(i, j, k, sum) shared(L, U, A, \
                                                                    MatrixDim)
#endif
  for (i = 0; i < MatrixDim; i++) {
    for (j = 0; j < MatrixDim; j++) {
      sum = 0;
      for (k = 0; k < MatrixDim; k++)
        sum += L[i][k] * U[k][j];
      A[i][j] = sum;
    }
  }
			dummyMethod2();

			dummyMethod3();
  for (i = 0; i < MatrixDim; i++) {
    for (j = 0; j < MatrixDim; j++)
      fprintf(fl, "%f ", L[i][j]);
    fprintf(fl, "\n");
  }
			dummyMethod4();
  fclose(fl);

			dummyMethod3();
  for (i = 0; i < MatrixDim; i++) {
    for (j = 0; j < MatrixDim; j++)
      fprintf(fu, "%f ", U[i][j]);
    fprintf(fu, "\n");
  }
			dummyMethod4();
  fclose(fu);

  fprintf(fa, "%d\n", MatrixDim);
			dummyMethod3();
  for (i = 0; i < MatrixDim; i++) {
    for (j = 0; j < MatrixDim; j++)
      fprintf(fa, "%f ", A[i][j]);
    fprintf(fa, "\n");
  }
			dummyMethod4();
  fclose(fa);

			dummyMethod3();
  for (i = 0; i < MatrixDim; i++) {
    free(L[i]);
    free(U[i]);
    free(A[i]);
  }
			dummyMethod4();
  free(L);
  free(U);
  free(A);

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