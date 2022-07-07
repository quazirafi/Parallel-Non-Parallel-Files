#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
main ()
{
  int i;
  int level = -1;

#pragma omp target map(tofrom : level)
  {
    level = omp_get_level ();
  }

  if (level != 0)
    __builtin_abort ();

#pragma omp target teams map(tofrom : level)
dummyMethod1();
#pragma omp distribute parallel for default(none) private(i) shared(level)
  for (i = 0; i < 1; ++i)
    level += omp_get_level ();

  if (level != 1)
dummyMethod2();
    __builtin_abort ();

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