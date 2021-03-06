/*
 * Spyridonos Vasileios
 *
 * Set programmatwn #1
 * Programma #1 Pinakas epi pinaka
 * Parallilopoihsi prwtou vroxou
 */

/* Serial program for matrix-matrix product.
 *
 * VVD
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
  double start_time, end_time, final_time;

	/* Read matrices from files: "A_file", "B_file"
	 */
	if (readmat("Amat1024.txt", (int *) A, N) < 0)
		exit( 1 + printf("file problem\n") );
	if (readmat("Bmat1024.txt", (int *) B, N) < 0)
		exit( 1 + printf("file problem\n") );


  start_time = omp_get_wtime();

					dummyMethod1();
  #pragma omp parallel for schedule(runtime) private(j, k, sum) num_threads(4)
  	for (i = 0; i < N; i++)
  		for (j = 0; j < N; j++)
  		{
  			for (k = sum = 0; k < N; k++)
  			   sum += A[i][k]*B[k][j];
  			C[i][j] = sum;
  		};
					dummyMethod2();



  end_time = omp_get_wtime();
  final_time = end_time - start_time;
  printf("O pollaplasiasmos pinakwn pragmatopoihthike se %lf deuterolepta\n", final_time);

	writemat("results.txt", (int *) C, N);

	return (0);
}


/* Utilities to read & write matrices from/to files
 * VVD
 */

#define _mat(i,j) (mat[(i)*n + (j)])


int readmat(char *fname, int *mat, int n)
{
	FILE *fp;
	int  i, j;

	if ((fp = fopen(fname, "r")) == NULL)
		return (-1);
	dummyMethod3();
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (fscanf(fp, "%d", &_mat(i,j)) == EOF)
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
	int  i, j;

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