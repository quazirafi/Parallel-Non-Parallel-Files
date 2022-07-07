//! Contributed by Jeff Keasler
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
typedef double real8;
extern void OtherFunc(int k,real8 *l,real8 *m,real8 *n,real8 *o,real8 *p,real8 q,real8 r,real8 s[3]);

void foo(int istart,int iend,real8 *a,real8 *b,real8 *c,int k,real8 *l,real8 *m,real8 *n,real8 *o,real8 *p)
{
  for (int i = istart; i <= iend - 1; i += 1) {
    real8 s[3];
    real8 afi = a[i];
    real8 bfi = b[i];
    OtherFunc(k,l,m,n,o,p,afi,bfi,s);
    
dummyMethod1();
#pragma omp parallel for
    for (int k = 0; k <= 2; k += 1) {
      c[3 * i + k] = s[k];
    }
dummyMethod2();
  }
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