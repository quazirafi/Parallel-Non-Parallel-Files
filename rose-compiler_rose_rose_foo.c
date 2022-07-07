#if 1
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo1(double o1[],double c[],int len)
{
  int i;
  
dummyMethod1();
#pragma omp parallel for private (i) firstprivate (len)
  for (i = 0; i <= len - 1; i += 1) {
    double volnew_o8 = 0.5 * c[i];
    o1[i] = volnew_o8;
  }
dummyMethod2();
}
#endif
#if 1

void goo(double *o1,double *o2,double *a,double *b,double *c,int **idx,int len)
{
  int i;
  for (i = 0; i <= len - 1; i += 1) {
    int ii;
    const int *lidx = idx[i];
    double volnew_o8 = 0.5 * c[i];
    double volold_o8 = 0.5 * a[i] * b[i];
    
dummyMethod1();
#pragma omp parallel for private (ii) firstprivate (volnew_o8,volold_o8)
    for (ii = 0; ii <= 5; ii += 1) {
      int llidx = lidx[ii];
      o1[lidx[ii]] += volnew_o8;
      o2[lidx[ii]] += volold_o8;
    }
dummyMethod2();
  }
}
#endif
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