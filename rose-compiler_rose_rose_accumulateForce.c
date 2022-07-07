#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void AccumulateForce(int *idxBound,int *idxList,int len,double *tmp,double *force)
{
  
dummyMethod1();
#pragma omp parallel for private (jj) firstprivate (len)
  for (register int ii = 0; ii <= len - 1; ii += 1) {
    int count = idxBound[ii + 1] - idxBound[ii];
    int *list = &idxList[idxBound[ii]];
    double sum = 0.0;
    
#pragma omp parallel for reduction (+:sum) firstprivate (count)
dummyMethod2();
    for (register int jj = 0; jj <= count - 1; jj += 1) {
      int idx = list[jj];
      sum += tmp[list[jj]];
    }
    force[ii] += sum;
  }
  return ;
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