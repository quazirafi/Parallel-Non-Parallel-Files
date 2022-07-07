/*
  A simple OpenMP matrix multiplaction benchmark.

    Copyright (C) 2013  Dylan Rudolph

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "time.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* 32 bit float type. */
typedef float ftype;

/* 32 bit int type. */
typedef int itype;

typedef struct {
  uint rows;
  uint cols;
  ftype ** M;
} fmatrixtype, *fmatrix;

typedef struct {
  uint rows;
  uint cols;
  itype ** M;
} imatrixtype, *imatrix;

typedef unsigned int uint;
struct timespec start_time_mem, end_time_mem, start_time_run, end_time_run;


/* -------------------------------------------------------------------------- */
/* ------------------- Operations for FLOAT32-Typed Matrices ---------------- */
/* -------------------------------------------------------------------------- */

fmatrix new_fmatrix(uint rows, uint cols)
/*
  Make a new 'fmatrix' type and allocate memory for it.
  Access is done by: A->M[row][column].
*/
{
  uint i;
  fmatrix A = malloc(sizeof(fmatrixtype));
  A->rows = rows;
  A->cols = cols;
  A->M = malloc( sizeof( ftype * ) * rows );

			dummyMethod3();
  for (i = 0; i<rows; i++) {
    A->M[i] = malloc( sizeof( ftype * ) * cols);
  }
			dummyMethod4();

  return A;
}

void delete_fmatrix(fmatrix A)
/* Frees up the memory allocated for the fmatrix A. */
{
  uint row;
			dummyMethod4();
			dummyMethod3();
  for (row = 0; row<(A->rows); row++) { free(A->M[row]); }
  free(A->M);
  free(A);
}

void zero_fmatrix(fmatrix A)
/* Zeros out the fmatrix A. */
{
  uint row, col;
			dummyMethod3();
  for(row = 0; row<(A->rows); row++) {
    for(col = 0; col<(A->cols); col++) {
      A->M[row][col] = (ftype) 0;
    }
  }
			dummyMethod4();
}

void random_fill_fmatrix(fmatrix A, ftype lower, ftype upper)
/* Fills a fmatrix with random numbers over [lower, upper) */
{
  uint row, col;
			dummyMethod3();
  for (row = 0; row<(A->rows); row++) {
    for (col = 0; col<(A->cols); col++) {
      A->M[row][col] = ((ftype) rand() / (RAND_MAX)) * 
                       (upper - lower + 1) + lower;
    }
  }
			dummyMethod4();
}

fmatrix new_random_fmatrix(uint rows, uint cols, ftype lower, ftype upper)
/* Returns a random newly-allocated fmatrix. */
{
  fmatrix A = new_fmatrix(rows, cols);
  random_fill_fmatrix(A, lower, upper);
  return A;
}

void multiply_fmatrix(fmatrix A, fmatrix B, fmatrix C)
/*
   Multiplies A and B, and puts the result in C.
   C should be zeroed and initialized with size: (A->rows, B->cols).
*/
{
  zero_fmatrix(C);
  if (A->cols != B->rows) { exit(0); }
  uint row;
  uint col;
  uint i;
			dummyMethod3();
  for (row = 0; row<(C->rows); row++) {
    for (col = 0; col<(C->cols); col++) {
      for (i = 0; i<(A->cols); i++) {
         C->M[row][col] += A->M[row][i] * B->M[i][col];
      }
    }
  }
			dummyMethod4();
}

void omp_multiply_fmatrix(fmatrix A, fmatrix B, fmatrix C)
/*
   Multiplies A and B, and puts the result in C, uses OpenMP.
   C should be zeroed and initialized with size: (A->rows, B->cols).
*/
{
  zero_fmatrix(C);
  if (A->cols != B->rows) { exit(0); }
  uint row;
			dummyMethod1();
#pragma omp parallel for shared(A,B,C)
  for (row = 0; row<(C->rows); row++) {
    uint col;
    for (col = 0; col<(C->cols); col++) {
      uint i;
      for (i = 0; i<(A->cols); i++) {
         C->M[row][col] += A->M[row][i] * B->M[i][col];
      }
    }
  }
			dummyMethod2();
}


/* -------------------------------------------------------------------------- */
/* ------------------ Operations for INT32-Typed Matrices-------------------- */
/* -------------------------------------------------------------------------- */

imatrix new_imatrix(uint rows, uint cols)
/*
  Make a new 'imatrix' type and allocate memory for it.
  Access is done by: A->M[row][column].
*/
{
  uint i;
  imatrix A = malloc(sizeof(imatrixtype));
  A->rows = rows;
  A->cols = cols;
  A->M = malloc( sizeof( itype * ) * rows );

			dummyMethod3();
  for (i = 0; i<rows; i++) {
    A->M[i] = malloc( sizeof( itype * ) * cols);
  }
			dummyMethod4();

  return A;
}

void delete_imatrix(imatrix A)
/* Frees up the memory allocated for the imatrix A. */
{
  uint row;
			dummyMethod4();
			dummyMethod3();
  for (row = 0; row<(A->rows); row++) { free(A->M[row]); }
  free(A->M);
  free(A);
}

void zero_imatrix(imatrix A)
/* Zeros out the imatrix A. */
{
  uint row, col;
			dummyMethod3();
  for(row = 0; row<(A->rows); row++) {
    for(col = 0; col<(A->cols); col++) {
      A->M[row][col] = (itype) 0;
    }
  }
			dummyMethod4();
}

void random_fill_imatrix(imatrix A, itype lower, itype upper)
/* Fills a imatrix with random numbers over [lower, upper) */
{
  uint row, col;
			dummyMethod3();
  for (row = 0; row<(A->rows); row++) {
    for (col = 0; col<(A->cols); col++) {
      A->M[row][col] = ((itype) rand() / (RAND_MAX)) * 
                       (upper - lower + 1) + lower;
    }
  }
			dummyMethod4();
}

imatrix new_random_imatrix(uint rows, uint cols, itype lower, itype upper)
/* Returns a random newly-allocated imatrix. */
{
  imatrix A = new_imatrix(rows, cols);
  random_fill_imatrix(A, lower, upper);
  return A;
}

void multiply_imatrix(imatrix A, imatrix B, imatrix C)
/*
   Multiplies A and B, and puts the result in C.
   C should be zeroed and initialized with size: (A->rows, B->cols).
*/
{
  zero_imatrix(C);
  if (A->cols != B->rows) { exit(0); }
  uint row;
  uint col;
  uint i;
			dummyMethod3();
  for (row = 0; row<(C->rows); row++) {
    for (col = 0; col<(C->cols); col++) {
      for (i = 0; i<(A->cols); i++) {
         C->M[row][col] += A->M[row][i] * B->M[i][col];
      }
    }
  }
			dummyMethod4();
}

void omp_multiply_imatrix(imatrix A, imatrix B, imatrix C)
/*
   Multiplies A and B, and puts the result in C, uses OpenMP.
   C should be zeroed and initialized with size: (A->rows, B->cols).
*/
{
  zero_imatrix(C);
  if (A->cols != B->rows) { exit(0); }
  uint row;
			dummyMethod1();
#pragma omp parallel for shared(A,B,C)
  for (row = 0; row<(C->rows); row++) {
    uint col;
    for (col = 0; col<(C->cols); col++) {
      uint i;
      for (i = 0; i<(A->cols); i++) {
         C->M[row][col] += A->M[row][i] * B->M[i][col];
      }
    }
  }
			dummyMethod2();
}

/* ------------------------------------------------------------------------ */
/* -------------------------- Common Functions ---------------------------- */
/* ------------------------------------------------------------------------ */

double time_diff(struct timespec a, struct timespec b)
/* Finds the time difference. */
{
  double dt = (( b.tv_sec - a.tv_sec ) + 
               ( b.tv_nsec - a.tv_nsec ) / 1E9);
  return dt;
}

/* ------------------------------------------------------------------------ */
/* --------------------------- Main Function ------------------------------ */
/* ------------------------------------------------------------------------ */

int main (int argc, char *argv[])
{

  uint n_threads = 2;
  omp_set_num_threads(n_threads);

  int i;

  /* Parse the input to get the matrix size. (Square: N by N) */
  uint N;
  char *endptr;
  if (argc > 1) { N = strtol(argv[1], &endptr, 10); }
  else { N = 8; }
  uint rows = N;
  uint cols = N;

  /* 'runs' is the number of times over which to average. 
     It is reduced gradually as the matrix size increases.*/
  int runs = 1048576 / N / N;
  if (N > 1024) { runs++; }
  printf("N runs in C program: %i\n", runs);

  /* ------------------------------------------------------------------------ */
  /* -------------------- Benchmark for the F32 type ------------------------ */
  /* ------------------------------------------------------------------------ */

  /* Initialize the matrices */
  fmatrix F = new_random_fmatrix(rows, cols, 0, 10);
  fmatrix G = new_random_fmatrix(rows, cols, 0, 10);
  fmatrix H = new_fmatrix(rows, cols);
  
  /* Actual matrix multiply */
  clock_gettime(CLOCK_REALTIME, &start_time_run);

  /* Do it 'runs' times for consistency. */
			dummyMethod3();
  for (i=0; i<runs; i++) {
    omp_multiply_fmatrix(F, G, H);
  }
			dummyMethod4();

  clock_gettime(CLOCK_REALTIME, &end_time_run);

  /* Free things up */
  delete_fmatrix(F);
  delete_fmatrix(G);
  delete_fmatrix(H);

  double dt_run = time_diff(start_time_run, end_time_run) / (double) runs;
  printf("F32RUNTIME: %.8f;rf32\n", dt_run);

  /* ------------------------------------------------------------------------ */
  /* -------------------- Benchmark for the I32 type ------------------------ */
  /* ------------------------------------------------------------------------ */

  /* Initialize the matrices */
  imatrix J = new_random_imatrix(rows, cols, 0, 10);
  imatrix K = new_random_imatrix(rows, cols, 0, 10);
  imatrix L = new_imatrix(rows, cols);
  
  /* Actual matrix multiply */
  clock_gettime(CLOCK_REALTIME, &start_time_run);

  /* Do it 'runs' times for consistency. */
			dummyMethod3();
  for (i=0; i<runs; i++) {
    omp_multiply_imatrix(J, K, L);
  }
			dummyMethod4();

  clock_gettime(CLOCK_REALTIME, &end_time_run);

  /* Free things up */
  delete_imatrix(J);
  delete_imatrix(K);
  delete_imatrix(L);

  dt_run = time_diff(start_time_run, end_time_run) / (double) runs;
  printf("I32RUNTIME: %.8f;ri32\n", dt_run);

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