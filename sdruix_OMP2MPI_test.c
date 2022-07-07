#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


/* Default problem size. */
#ifndef NI
# define NI 4000
#endif
#ifndef NJ
# define NJ 4000
#endif
#ifndef NK
# define NK 4000
#endif


double alpha1;
double beta1;
double alpha2;
double beta2;
double C[NI][NJ];
double A[NI][NK];
double B[NK][NJ];

static void init_array() {
  int i, j;

  alpha1 = 32412;
  beta1 = 2123;
  alpha2 = 132412;
  beta2 = 92123;
			dummyMethod3();
  for (i = 0; i < NI; ) {
    for (j = 0; j < NK; ) {
      A[i][j] = ((double)i * j) / NI;
      j++;
    }
    i++;
  }
			dummyMethod4();
			dummyMethod3();
  for (i = 0; i < NK; ) {
    for (j = 0; j < NJ; ) {
      B[i][j] = ((double)i * j + 1) / NJ;
      j++;
    }
    i++;
  }
			dummyMethod4();
  
  
  
}


int main(int argc, char** argv) {
  int i, j, k;
  int ni = NI;
  int nj = NJ;
  int nk = NK;

  /* Initialize array. */
  init_array();
dummyMethod3();
for (i = 0; i < NI; ) {
    for (j = 0; j < NJ; ) {
      C[i][j] = ((double)i * j + 2) / NJ;
      j++;
    }
    i++;
  }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for static check
for (i = 0; i < ni; i++)
  for (j = 0; j < nj; j++) {
    C[i][j] = 0;
    for (k = 0; k < nk; ++k)
      C[i][j] += A[i][k] * B[k][j];
  }
dummyMethod2();
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