#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MTRX_SIZE 1000
#define BLCK_SIZE 100

typedef int matrix[MTRX_SIZE][MTRX_SIZE];
typedef int block[BLCK_SIZE][BLCK_SIZE];

int rnd(int n) {
  return rand() % n;
}

void matrix_fill(matrix m) {
  int i, j;
dummyMethod3();
  for (i = 0; i < MTRX_SIZE; i++) {
    for (j = 0; j < MTRX_SIZE; j++) {
      m[i][j] = rnd(5);
    }
  }
dummyMethod4();
}

void matrix_print(matrix m) {
  int i, j;
dummyMethod3();
  for (i = 0; i < MTRX_SIZE; i++) {
    for (j = 0; j < MTRX_SIZE; j++) {
      printf("%4d", m[i][j]);
      if (j == MTRX_SIZE - 1) {
        printf("\n");
      }
    }
  }
dummyMethod4();
}

void block_add(block b1, block b2) {
  int i, j;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      b1[i][j] += b2[i][j];
    }
  }
			dummyMethod4();
}

void block_mul(block b1, block b2, block b3) {
  int i, j, k;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      b3[i][j] = 0;
      for (k = 0; k < BLCK_SIZE; k++) {
        b3[i][j] += b1[i][k] * b2[k][j];
      }
    }
  }
			dummyMethod4();
}

void block_get(block b, matrix m, int k, int l) {
  int i, j;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      b[i][j] = m[BLCK_SIZE * k + i][BLCK_SIZE * l + j];
    }
  }
			dummyMethod4();
}

void block_set(block b, matrix m, int k, int l) {
  int i, j;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      m[BLCK_SIZE * k + i][BLCK_SIZE * l + j] = b[i][j];
    }
  }
			dummyMethod4();
}

void block_print(block b) {
  int i, j;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      printf("%4d", b[i][j]);
      if (j == BLCK_SIZE - 1) {
        printf("\n");
      }
    }
  }
			dummyMethod4();
}

void block_reset(block b) {
  int i, j;
			dummyMethod3();
  for (i = 0; i < BLCK_SIZE; i++) {
    for (j = 0; j < BLCK_SIZE; j++) {
      b[i][j] = 0;
    }
  }
			dummyMethod4();
}

void matrix_mul(matrix m1, matrix m2, matrix m3) {
  int i, j, k;
  block b1, b2, b_mul, b_sum;
  for (i = 0; i < MTRX_SIZE / BLCK_SIZE; i++) {
							dummyMethod1();
  #pragma omp parallel for schedule(dynamic)
    for (j = 0; j < MTRX_SIZE / BLCK_SIZE; j++) {
      block_reset(b_sum);
      for (k = 0; k < MTRX_SIZE / BLCK_SIZE; k++) {
        block_get(b1, m1, i, k);
        block_get(b2, m2, k, j);
        block_mul(b1, b2, b_mul);
        block_add(b_sum, b_mul);
      }
      block_set(b_sum, m3, i, j);
    }
							dummyMethod2();
  }
}

matrix *matrix_new(void) {
  return malloc(sizeof(matrix));
}

void sep(void) {
  printf("\n");
}

int main() {
  matrix *m1, *m2, *m3;
  m1 = matrix_new();
  m2 = matrix_new();
  m3 = matrix_new();

  matrix_fill(*m1);
  matrix_fill(*m2);
  matrix_mul(*m1, *m2, *m3);

  /* matrix_print(*m1); */
  /* sep(); */
  /* matrix_print(*m2); */
  /* sep(); */
  /* matrix_print(*m3); */

  free(m1);
  free(m2);
  free(m3);
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