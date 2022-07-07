#include "include/gaussian_elimination.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Used to store the Maximum value row
typedef struct {
  int index;
  double value;
} Maximum;

// function for elementary operation of swapping two rows
void SwapRow(double *pMatrix, double *pVector, int i, int j, int Size) {
  double pVectorTemp = pVector[i];
  pVector[i] = pVector[j];
  pVector[j] = pVectorTemp;

dummyMethod3();
  for (int k=0;  k<= Size; k++) {
    double pMatrixTemp = pMatrix[i * Size + k];

    pMatrix[i * Size + k] = pMatrix[j * Size + k];
    pMatrix[j * Size + k] = pMatrixTemp;
  }
dummyMethod4();
}

void ParallelGaussianElimination(double *pMatrix, double *pVector, int Size) {
  double multiplier;

  for (int k = 0; k < Size; k++) {
    Maximum maximum  = { k, pMatrix[k * Size + k] };

    // Custom reduction
    // it is called get_maximum, return a a value of type Maximum.
    // omp_out and omp_in are the predefined names of two private elements
    // to combine in the end to the final shared variable.
    #pragma omp declare reduction(get_maximum : Maximum :\
        omp_out = omp_out.value > omp_in.value ? omp_out : omp_in)\
        initializer (omp_priv=(omp_orig))

							dummyMethod1();
    #pragma omp parallel for reduction(get_maximum : maximum) num_threads(NUM_THREADS)
    for (int i = k + 1; i < Size; i++)
      if (fabs(pMatrix[i * Size + k]) > maximum.value)
        maximum.value = pMatrix[i * Size + k], maximum.index = i;
							dummyMethod2();

    if (maximum.index != k)
      SwapRow(pMatrix, pVector, k, maximum.index, Size);

							dummyMethod1();
    #pragma omp parallel for shared(pMatrix, pVector) private(multiplier) num_threads(NUM_THREADS)
    for (int i = k + 1; i < Size; i++) {
      multiplier = pMatrix[i * Size + k] / pMatrix[k * Size + k];
  
      for (int j = k + 1; j <= Size; j++)
        pMatrix[i * Size + j] -= pMatrix[k * Size + j] * multiplier;

      pMatrix[i * Size + k] = 0;
      pVector[i] -= pVector[k] * multiplier;
    }
							dummyMethod2();
  }
}

void BackSubstitution(double *pMatrix, double *pVector, double *pResult, int Size) {
			dummyMethod1();
  #pragma omp parallel for shared(pMatrix, pVector, pResult) num_threads(NUM_THREADS)
  for (int i = Size - 1; i >= 0; i--) {
    pResult[i] = pVector[i];

    for (int j = i + 1; j < Size; j++)
      pResult[i] -= pMatrix[i * Size + j] * pResult[j];

    pResult[i] /= pMatrix[i * Size + i];
  }
			dummyMethod2();
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