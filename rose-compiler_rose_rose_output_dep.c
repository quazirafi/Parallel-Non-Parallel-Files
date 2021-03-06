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
/*  carryLevel should be 0?
 
 * dep SgExprStatement:x = i; SgExprStatement:x = i; 1*1 SCALAR_DEP; commonlevel = 1 CarryLevel = 1 SgVarRefExp:x@7:6->SgVarRefExp:x@7:6 == 0;||::
 */
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