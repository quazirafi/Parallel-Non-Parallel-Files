#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int kernel() {
  int ni;int nj;int nk;int nl;int nm;double A[128 + 0][128 + 0];double B[128 + 0][128 + 0];double C[128 + 0][128 + 0];double D[128 + 0][128 + 0];
  int c2;
  int c1;
  ni=3;nj=5;nk=2;nl=4;nm=3;c2=0;c1=0;
  if (nj >= 1 && nl <= 0) {
dummyMethod1();
#pragma omp parallel for private(c2)
    for (c1 = nj; c1 <= ((((ni + -1 < nk + -1?ni + -1 : nk + -1)) < nm + -1?((ni + -1 < nk + -1?ni + -1 : nk + -1)) : nm + -1)); c1++) {
      for (c2 = 0; c2 <= nj + -1; c2++) {
        A[c1][c2] = ((double )c1) * c2 / ni;
        B[c1][c2] = ((double )c1) * (c2 + 1) / nj;
      }
      for (c2 = nj; c2 <= nk + -1; c2++) {
        A[c1][c2] = ((double )c1) * c2 / ni;
      }
    }
dummyMethod2();
    }
  if (nj >= 1) {
dummyMethod1();
#pragma omp parallel for private(c2)
    for (c1 = (nj > nm?nj : nm); c1 <= ((ni + -1 < nk + -1?ni + -1 : nk + -1)); c1++) {
      for (c2 = 0; c2 <= nj + -1; c2++) {
        A[c1][c2] = ((double )c1) * c2 / ni;
        B[c1][c2] = ((double )c1) * (c2 + 1) / nj;
      }
      for (c2 = nj; c2 <= nk + -1; c2++) {
        A[c1][c2] = ((double )c1) * c2 / ni;
      }
    }
dummyMethod2();
  }
}

int main() {
  function();
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