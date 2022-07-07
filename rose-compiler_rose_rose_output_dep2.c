// an example of output dependence preventing parallelization
// loop carried vs. non-loop carried output dependence!
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo()
{
  int i;
  int x;
  int y;
  
dummyMethod1();
#pragma omp parallel for private (x,y,i)
  for (i = 0; i <= 99; i += 1) {
    x = i;
    y = i;
    y = i + 1;
  }
dummyMethod2();
}
/*  
output dependence   carryLevel should be 0?  carry level is wrong!!
dep SgExprStatement:x = i; 
    SgExprStatement:x = i; 
    1*1 SCALAR_DEP; commonlevel = 1 CarryLevel = 1 
    SgVarRefExp:x@8:6->SgVarRefExp:x@8:6 == 0;||::
output dependence   carryLevel should be 0?  carry level is wrong!!
dep SgExprStatement:y = i; SgExprStatement:y = i; 1*1 SCALAR_DEP; commonlevel = 1 CarryLevel = 1 SgVarRefExp:y@9:6->SgVarRefExp:y@9:6 == 0;||::
output dependence   carryLevel should be 0?  carry level is wrong!!
dep SgExprStatement:y =(i + 1); SgExprStatement:y =(i + 1); 1*1 SCALAR_DEP; commonlevel = 1 CarryLevel = 1 SgVarRefExp:y@10:6->SgVarRefExp:y@10:6 == 0;||::
//--------------
output dependence: non-loop carried, level =1 is correct
dep SgExprStatement:y = i; SgExprStatement:y =(i + 1); 1*1 SCALAR_DEP; commonlevel = 1 CarryLevel = 1 SgVarRefExp:y@9:6->SgVarRefExp:y@10:6 == 0;||::
 output dependence: Carry level =0 means loop carried, also look at line number: 10>9 
dep SgExprStatement:y =(i + 1); SgExprStatement:y = i; 1*1 SCALAR_BACK_DEP; commonlevel = 1 CarryLevel = 0 SgVarRefExp:y@10:6->SgVarRefExp:y@9:6 <= -1;||::
 
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