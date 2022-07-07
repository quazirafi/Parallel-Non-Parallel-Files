#include "lu.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define DEBUG_VERBOSE_INVERSE 0
#define DEBUG_LU_DECOMPOSITION_TEST 0

SquareMatrix* getL(SquareMatrix *mat) {
  int s = mat->size;
  SquareMatrix *mat_ret = createIdentityMatrix(s);
  long double **m_src = mat->matrix;
  long double **m_dest = mat_ret->matrix;
  int i, j;
dummyMethod1();
  #pragma omp parallel for private(i, j) shared(s, m_dest, m_src)
    for (i = 1; i < s; ++i) {
      for (j = 0; j < i; ++j) {
        m_dest[i][j] = m_src[i][j];
      }
    }
dummyMethod2();
  return mat_ret;
}

SquareMatrix* getU(SquareMatrix *mat) {
  int s = mat->size;
  SquareMatrix *mat_ret = createMatrix(s);
  long double **m_src = mat->matrix;
  long double **m_dest = mat_ret->matrix;
  int i, j;
dummyMethod1();
  #pragma omp parallel for private(i, j) shared(s, m_dest, m_src)
    for (i = 0; i < s; ++i) {
      for (j = i; j < s; ++j) {
        m_dest[i][j] = m_src[i][j];
      }
    }
dummyMethod2();
  return mat_ret;
}

SquareMatrix* getLInverse(SquareMatrix *mat_L) {
  int s = mat_L->size;
  SquareMatrix *mat_ret = createMatrix(s);
  SquareMatrix *mat_I = createIdentityMatrix(s);
  long double **m_L = mat_L->matrix;
  long double **m_I = mat_I->matrix;
  long double **m = mat_ret->matrix;
  int i, k, j;
  long double sum;
							dummyMethod1();
  #pragma omp parallel for private(i, j, k) shared(s, m, m_I, m_L) reduction(+:sum)
    for(k = 0; k < s; ++k) {
      for(i = k; i < s; ++i) {
        sum = 0.0;
        for(j = k; j < i; ++j) sum +=  m_L[i][j] * m[j][k];
          m[i][k] = (m_I[i][k] - sum) / m_L[i][i];
      }
    }
							dummyMethod2();
  freeMatrix(mat_I);
  return mat_ret;
}

SquareMatrix* getUInverse(SquareMatrix *mat_U) {
  int s = mat_U->size;
  SquareMatrix *mat_ret = createMatrix(s);
  SquareMatrix *mat_I = createIdentityMatrix(s);
  long double **m_U = mat_U->matrix;
  long double **m_I = mat_I->matrix;
  long double **m = mat_ret->matrix;
  int i, j, k;
  long double sum;
							dummyMethod1();
  #pragma omp parallel for private(i, j, k) shared(s, m, m_I, m_U) reduction(+:sum)
    for(k = 0; k < s; ++k) {
      for(i = k; i >= 0; --i) {
        sum = 0.0;
        for(j = i+1; j <= k; ++j) sum +=  m_U[i][j] * m[j][k];
          m[i][k] = (m_I[i][k] - sum) / m_U[i][i];
      }
    }
							dummyMethod2();
  freeMatrix(mat_I);
  return mat_ret;
}

int doolittle(SquareMatrix *mat_A, SquareMatrix *mat_LU) {
  assert(mat_A->size == mat_LU->size);
  long double **matrixA = mat_A->matrix;
  long double **matrixLU = mat_LU->matrix;
  int ret = 0;
  int i, j, k;
  long double sum;
  int s = mat_A->size;
			dummyMethod3();
  for(j = 0; j < s; ++j) {
    for(i = 0; i <= j; ++i) {
      sum = 0.0;
//#pragma omp parallel for firstprivate(i, j) private(k) shared(matrixLU) reduction(+:sum)
      for(k = 0; k < i; ++k) {
        sum +=  matrixLU[i][k] * matrixLU[k][j];
      }
      matrixLU[i][j] = matrixA[i][j] - sum;
    }
    for(i = j + 1; i < s; ++i) {
      sum = 0.0;
//#pragma omp parallel for firstprivate(i, j) private(k) shared(matrixLU) reduction(+:sum)
      for(k = 0; k < j; ++k) {
        sum += matrixLU[i][k] * matrixLU[k][j];
      }
      matrixLU[i][j] = (matrixA[i][j] - sum) / matrixLU[j][j];
    }
  }
			dummyMethod4();
  return ret;
}

int cholesky(SquareMatrix *A, SquareMatrix *mat_LU) {
  assert(A->size == mat_LU->size);
  long double **matrixA = A->matrix;
  long double **matrixLU = mat_LU->matrix;
  int ret = 0;
  int i, j, k;
  long double sum;
  int s = A->size;
			dummyMethod3();
  for(k = 0; k < s; ++k) {
    sum = 0.0;
    //#pragma omp parallel for firstprivate(k) private(j) shared(matrixLU) reduction(+:sum)
    for(j = 0; j < k; ++j) {
      sum += matrixLU[k][j] * matrixLU[k][j];
    }
    matrixLU[k][k] = sqrt(matrixA[k][k] - sum);
    for(i = k+1; i < s; ++i){
      sum = 0.0;
      //#pragma omp parallel for firstprivate(i, k) private(j) shared(matrixLU) reduction(+:sum)
      for(j = 0; j < k; ++j) {
        sum+= matrixLU[i][j] * matrixLU[k][j];
      }
      assert(matrixLU[k][k] != 0.0);
      matrixLU[i][k] = (matrixA[i][k] - sum) / matrixLU[k][k];
    }
  }
			dummyMethod4();
  return ret;
}

int choleskyRow(SquareMatrix *A, SquareMatrix *mat_LU) {
  assert(A->size == mat_LU->size);
  long double **matrixA = A->matrix;
  long double **matrixLU = mat_LU->matrix;
  int ret = 0;
  int i, j, k;
  long double sum;
  int s = A->size;
			dummyMethod3();
  for(i = 0; i < s; ++i) {
    for(j = 0; j < s; ++j) {
      sum = 0.0;
      //#pragma omp parallel for firstprivate(i, j) private(k) shared(matrixLU) reduction(+:sum)
      for(k = 0; k < j; ++k) {
        sum += matrixLU[i][k] * matrixLU[j][k];
      }
      matrixLU[i][j] = (matrixA[i][j] - sum) / matrixLU[j][j];
    }
    sum = 0.0;
    //#pragma omp parallel for firstprivate(i) private(k) shared(matrixLU) reduction(+:sum)
    for(k = 0; k < i; ++k) {
      sum += matrixLU[i][k] * matrixLU[i][k];
    }
    matrixLU[i][i] = sqrt(matrixA[i][i] - sum);
  }
			dummyMethod4();
  return ret;
}

SquareMatrix* getInverseMatrixFromLU(SquareMatrix *mat_LU) {
  int s = mat_LU->size;
  SquareMatrix *mat_ret = createMatrix(s);
  SquareMatrix *mat_I = createIdentityMatrix(s);
  long double **m_LU = mat_LU->matrix;
  long double **m_ret = mat_ret->matrix;
  long double **m_I = mat_I->matrix;
  int i, j, k;
  long double sum, y[s];
    for(k = 0; k < s; k++) {
      for(i = 0; i < s; i++) {
        sum = 0.0;
															dummyMethod1();
        #pragma omp parallel for firstprivate(k, i) private(j) shared(m_LU, y) reduction(+:sum)
        for(j = 0; j <= i-1; j++) {
          sum += m_LU[i][j] * y[j];
        }
															dummyMethod2();
        y[i] = (m_I[i][k] - sum);
      }
      for(i = s-1; i >= 0; i--) {
        sum = 0.0;
															dummyMethod1();
        #pragma omp parallel for firstprivate(k, i) private(j) shared(m_LU, m_ret) reduction(+:sum)
        for(j = i+1; j < s; j++) {
          sum += m_LU[i][j] * m_ret[j][k];
        }
															dummyMethod2();
        m_ret[i][k] = (y[i] - sum) / m_LU[i][i];
      }
    }
  freeMatrix(mat_I);
  return mat_ret;
}

SquareMatrix* inverse(SquareMatrix *mat_A) {
  int s = mat_A->size;
  SquareMatrix *LU = createMatrix(s);
  SquareMatrix *mat_ret;
  if(0 && isSymmetric(mat_A)) {
    cholesky(mat_A, LU);
    SquareMatrix *L_1 = getLInverse(LU);
    SquareMatrix *L_1_T = transpose(L_1);
    mat_ret =  multiply(L_1_T, L_1);
    #if DEBUG_VERBOSE_INVERSE
      printMatrixWithName(LU, "LU cholesky");
      printMatrixWithName(L_1, "L^(-1)");
      printMatrixWithName(L_1_T, "(L^(-1))^T");
    #endif
    freeMatrix(L_1);
    freeMatrix(L_1_T);
  }
  else {
    doolittle(mat_A, LU);
    SquareMatrix *L = getL(LU);
    SquareMatrix *U = getU(LU);
    #if DEBUG_LU_DECOMPOSITION_TEST
      SquareMatrix *A_ = multiply(L, U);
      #if DEBUG_VERBOSE_INVERSE
        printMatrixWithName(mat_A, "A");
        printMatrixWithName(A_, "A'");
      #endif
      int cI = checkIdentity(mat_A, A_);
      printf("%s\n", cI == 0 ? "A == A'" : (cI > 1 ? "A < A'" : "A < A'"));
      freeMatrix(A_);
    #endif
    SquareMatrix *L_1 = getLInverse(L);
    SquareMatrix *U_1 = getUInverse(U);
    mat_ret = multiply(U_1, L_1);
    #if DEBUG_VERBOSE_INVERSE
      printMatrixWithName(LU, "LU doolitle");
      printMatrixWithName(L, "L");
      printMatrixWithName(U, "U");
      printMatrixWithName(L_1, "L^(-1)");
      printMatrixWithName(U_1, "U^(-1)");
    #endif
    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(L_1);
    freeMatrix(U_1);
  }

  #if DEBUG_VERBOSE_INVERSE
    printMatrixWithName(mat_ret, "A^(-1)");
  #endif
  freeMatrix(LU);
  return mat_ret;
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