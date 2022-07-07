// an example of output dependence preventing parallelization
// x: not live-in, yes live-out
//    outer scope
//    loop-carried output-dependence: x=... : accept values based on loop variable; or not. 
//Solution: Can be parallelized using lastprivate(x)
#include <stdio.h> 
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo()
{
  int i;
  int x;
  
dummyMethod1();
#pragma omp parallel for private (i) lastprivate (x)
  for (i = 0; i <= 99; i += 1) {
    x = i;
  }
dummyMethod2();
  printf("x=%d",x);
}
/*  
 * output dependence, loop carried
 * 1*1  SCALAR_DEP DATA_DEP; commonlevel = 1 CarryLevel = 0 Scalar dep type  OUTPUT_DEP DATA_DEP;SgVarRefExp:x@12:6->SgVarRefExp:x@12:6 == 0;||::
 */
// This x should be not lastprivate since it is live-in
// x is both live-in and live-out, and written, cannot be reduction
// So, the loop cannot be parallelized

void foo2()
{
  int a[100];
  int i;
  int x = 10;
			dummyMethod3();
  for (i = 0; i <= 99; i += 1) {
    a[i] = x;
    x = i;
  }
			dummyMethod4();
  printf("x=%d",x);
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