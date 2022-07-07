/// \file
/// Matrix I/O.

#include "matrixio.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdio.h>
#include <math.h>

#include "sparseMatrix.h"
#include "constants.h"

/// \details
/// Write out sparsity from sparse matrix. 
void writeSparsePattern(char* fname, struct SparseMatrixSt* spmatrix, real_t hthresh)
{
  int spmatrix_hsize = spmatrix->hsize; 
  // char hrow[spmatrix->hsize];
  char *hrow = (char*)malloc(spmatrix->hsize * sizeof(char));
  FILE* sFile;

  sFile = fopen(fname, "w");
  
			dummyMethod1();
  #pragma omp parallel for
  for (int i = 0; i < spmatrix_hsize; i++)
  {
    for (int j = 0; j < spmatrix->hsize; j++)
    {
      hrow[j] = '.';
    }

    for (int j = 0; j < spmatrix->iia[i]; j++)
    {
      if (ABS(spmatrix->val[i][j]) > hthresh)
      {
        hrow[spmatrix->jja[i][j]] = '*';
      }
    }

    for (int j = 0; j < spmatrix->hsize;j++)
    {
      fprintf(sFile, "%c", hrow[j]);
    }
    fprintf(sFile, "\n");

  }
			dummyMethod2();
  free(hrow);
  fclose(sFile);
}

/// \details
/// Read in hamiltonian matrix from file in Matrix Market format.
void readMTX(char* fname, struct SparseMatrixSt* hmatrix)
{
  int hvalue, msum, irow, icol, ind;
  char line[100], header1[20], header2[20], header3[20], header4[20], header5[20];
  double value;
  FILE* hFile;

  hFile = fopen(fname, "r");

  // Read in header
  fscanf(hFile, "%s %s %s %s %s", header1, header2, header3, header4, header5); 

  // Read in dimensions of matrix as dense and the number of sparse elements
  fscanf(hFile, "%d %d %d", &hvalue, &hvalue, &msum);

  // Read in elements for sparse matrix
  // Read in as 1-based
			dummyMethod3();
  for (int i = 0; i < msum; i++)
  {
    fscanf(hFile, "%d %d %lg", &irow, &icol, &value);
    irow--; icol--;
    ind = hmatrix->iia[irow];
    hmatrix->jja[irow][ind] = icol;
    hmatrix->val[irow][ind] = value;
    hmatrix->iia[irow]++;
  }
			dummyMethod4();

  fclose(hFile);
}

/// \details
/// Write out sparse matrix in Matrix market format.
void writeMTX(char* fname, struct SparseMatrixSt* spmatrix)
{
  FILE* mFile;
  int msum;

  mFile = fopen(fname, "w");

  // Write header
  fprintf(mFile, "=====MatrixMarket matrix coordinate real general\n");

  // Collect number of non-zero elements
  // Write out matrix size as dense and number of non-zero elements
  msum = 0;
			dummyMethod3();
  for (int i = 0; i < spmatrix->hsize; i++)
  {
    msum += spmatrix->iia[i];
  }
			dummyMethod4();
  fprintf(mFile, "%d %d %d\n", spmatrix->hsize, spmatrix->hsize, msum);

  // Write out non-zero elements
			dummyMethod3();
  for (int i = 0; i < spmatrix->hsize; i++)
  {
    for (int j = 0; j < spmatrix->iia[i]; j++)
    {
      fprintf(mFile, "%d %d %lg\n", i+1, spmatrix->jja[i][j]+1, spmatrix->val[i][j]);
    }
  }
			dummyMethod4();

  fclose(mFile);
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