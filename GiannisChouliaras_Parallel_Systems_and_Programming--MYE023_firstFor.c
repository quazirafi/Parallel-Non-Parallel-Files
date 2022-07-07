/* Serial program for matrix-matrix product.
 *
 * VVD
 */

/**
 * name: Ioannis Chouliaras
 * AM  : 2631
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1024
int A[N][N], B[N][N], C[N][N];
int readmat(char *fname, int *mat, int n),
    writemat(char *fname, int *mat, int n);

int main()
{
  int i, j, k, sum;
  double start, end;

  /* Read matrices from files: "A_file", "B_file"
   */
  if (readmat("Amat1024.txt", (int *)A, N) < 0)
    exit(1 + printf("file problem\n"));
  if (readmat("Bmat1024.txt", (int *)B, N) < 0)
    exit(1 + printf("file problem\n"));

  // set number of threads to 4 :
  omp_set_num_threads(4);
  start = omp_get_wtime();
			dummyMethod1();
  #pragma omp parallel for private(j, k, sum) schedule(dynamic)
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      for (k = sum = 0; k < N; k++)
        sum += A[i][k] * B[k][j];
      C[i][j] = sum;
    };
  }
			dummyMethod2();
  end = omp_get_wtime();
  printf("Work took %.2f seconds\n", end - start);

  /* Save result in "Cmat1024"
   */
  writemat("Cmat1024.txt", (int *)C, N);

  return (0);
}

/* Utilities to read & write matrices from/to files
 * VVD
 */

#define _mat(i, j) (mat[(i)*n + (j)])

int readmat(char *fname, int *mat, int n)
{
  FILE *fp;
  int i, j;
  if ((fp = fopen(fname, "r")) == NULL)
    return (-1);
			dummyMethod3();
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (fscanf(fp, "%d", &_mat(i, j)) == EOF)
      {
        fclose(fp);
        return (-1);
      };
			dummyMethod4();
  fclose(fp);
  return (0);
}

int writemat(char *fname, int *mat, int n)
{
  FILE *fp;
  int i, j;

  if ((fp = fopen(fname, "w")) == NULL)
    return (-1);
			dummyMethod3();
  for (i = 0; i < n; i++, fprintf(fp, "\n"))
    for (j = 0; j < n; j++)
      fprintf(fp, " %d", _mat(i, j));
			dummyMethod4();
  fclose(fp);
  return (0);
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