#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NRA 800 /* number of rows in matrix A */
#define NCA 800 /* number of columns in matrix A */
#define NCB 800 /* number of columns in matrix B */

void matrix_mult(void);

int main() {
  matrix_mult();

  return 0;
}

void matrix_mult() {
  int i, j, k;

  /* matrix A to be multiplied */
  double **a = (double **)malloc(sizeof(double *) * NRA);
dummyMethod3();
  for (i = 0; i < NRA; i++) {
    a[i] = (double *)malloc(sizeof(double) * NCA);
  }
dummyMethod4();

  /* matrix B to be multiplied */
  double **b = (double **)malloc(sizeof(double *) * NCA);
dummyMethod3();
  for (i = 0; i < NCA; i++) {
    b[i] = (double *)malloc(sizeof(double) * NCB);
  }
dummyMethod4();

  /* result matrix C */
  double **c = (double **)malloc(sizeof(double *) * NRA);
			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    c[i] = (double *)malloc(sizeof(double) * NCB);
  }
			dummyMethod4();

  /* initialize matrices */
			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    for (j = 0; j < NCA; j++) {
      a[i][j] = i + j;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NCA; i++) {
    for (j = 0; j < NCB; j++) {
      b[i][j] = i * j;
    }
  }
			dummyMethod4();

			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    for (j = 0; j < NCB; j++) {
      c[i][j] = 0;
    }
  }
			dummyMethod4();

/* matrix-matrix multiplication */
			dummyMethod1();
#pragma omp parallel for private(i, j, k)
  for (i = 0; i < NRA; i++) {
    for (j = 0; j < NCB; j++) {
      for (k = 0; k < NCA; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
			dummyMethod2();

  /* print results */
			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    for (j = 0; j < NCB; j++) {
      printf("%10.2f  ", c[i][j]);
    }
    printf("\n");
  }
			dummyMethod4();

  /* free memory */
			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    free(a[i]);
  }
			dummyMethod4();
  free(a);

			dummyMethod3();
  for (i = 0; i < NCA; i++) {
    free(b[i]);
  }
			dummyMethod4();
  free(b);

			dummyMethod3();
  for (i = 0; i < NRA; i++) {
    free(c[i]);
  }
			dummyMethod4();
  free(c);
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