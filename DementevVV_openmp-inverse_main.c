#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include "omp.h"
#include "lu.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void generateMatrix(int n, long double *matrix[]);
void saveResults(int size, struct timeval begin, struct timeval end, int nthreads);
void ShowUsage () {
  printf (
  "Usage:\n"
  "  inverseMatrix  -h | -help | --help   : print help\n"
  "Options:\n"
  "  -n [N]           : generate matrix size N to inverse\n"
  "  -n [N]           : N == 0 start demo\n"
  "  -t [T]           : number of threads (default T==2)\n"
  );
}

int main(int argc, char *argv[]) {
  if ((argc < 2) || strcmp (argv[1], "-h") == 0 || strcmp (argv[1], "-help") == 0 || strcmp (argv[1], "--help") == 0) {
    ShowUsage ();
    return 0;
  }
  int nthreads = 2;
  if (argc > 3) {
    if (strcmp (argv[3], "-t") == 0) {
      if (argc == 4) {
        ShowUsage ();
        return 0;
      }
      nthreads = atoi(argv[4]);
      int nthreadsMax = omp_get_max_threads();
      if (nthreads > nthreadsMax) nthreads = nthreadsMax;
      if (nthreads < 2) nthreads = 2;
    }
  }

  omp_set_num_threads(nthreads);
  if (argc > 2) {
    if (strcmp (argv[1], "-n") == 0) {
      int n = atoi(argv[2]);
      SquareMatrix *A;
      if (n == 0) {
        long double matrixToInverse[4][4] = { {10, 7, 8, 7}, {7, 5, 6, 5}, {8, 6, 10, 9}, {7, 5, 9, 10} };
        /* обратная матрица должна быть */
        /*  25 -41  10 -6 */
        /* -41  68 -17 10 */
        /*  10 -17   5 -3 */
        /*  -6  10  -3  2 */
        A = createMatrix(4);
        fillMatrix(A, matrixToInverse);
      }
      else {
        long double **matrixToInverse;
        int i;
        long double *data = (long double *) calloc(n *n, sizeof(long double)); // contigous memory
        matrixToInverse = (long double **)calloc(n, sizeof(long double *));
															dummyMethod3();
        for (i = 0; i < n; ++i)
          matrixToInverse[i] = &(data[n*i]);
															dummyMethod4();
        generateMatrix(n, matrixToInverse);
        A = createMatrix(n);
        fillMatrixDynamicArray(A, matrixToInverse);
        free(matrixToInverse[0]);
        free(matrixToInverse);
      }
      printMatrixWithName(A, "A");
      struct timeval begin, end;
      gettimeofday(&begin, NULL);
      SquareMatrix *A_1 = inverse(A);
      gettimeofday(&end, NULL);
      saveResults(n ? n : 4, begin, end, nthreads);
      printMatrixWithName(A_1, "A^(-1)");
      freeMatrix(A);
      freeMatrix(A_1);
    }
  }
  else { ShowUsage (); }
  return 0;
}

void generateMatrix(int n, long double *matrix[]) {
  int i, j;
							dummyMethod1();
  #pragma omp parallel for private(i, j) shared(matrix, n)
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        matrix[i][j] = 1.0 / (i + j + 1.0);
      }
    }
							dummyMethod2();
}

void saveResults(int size, struct timeval begin, struct timeval end, int nthreads) {
  FILE *fp = fopen("output.txt","a+");
  if (fp == NULL) perror ("Error opening file");
  else {
      fprintf(fp,"%d ", size);
      fprintf(fp,"%d ", nthreads);
      fprintf(fp,"%f\n", (double)((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 0.000001));
      fclose(fp);
  }
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