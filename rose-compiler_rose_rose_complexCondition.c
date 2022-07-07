// Contributed by Jeff Keasler
// 5/24/2010
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void goo(int numAB)
{
  double *c;
  double *bufLoc;
  int k_nom_22;
#if 0   
#else     
  
dummyMethod1();
#pragma omp parallel for private (k_nom_22) firstprivate (numAB)
  for (k_nom_22 = 0; k_nom_22 <= numAB * numAB * 3 - 1; k_nom_22 += 1) {
#endif     
dummyMethod2();
    bufLoc[k_nom_22] = c[k_nom_22];
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