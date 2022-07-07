#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a[64];

int
main ()
{
  int i;
dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 64; i++)
    a[i] = i;
  omp_pause_resource (omp_pause_soft, omp_get_initial_device ());
dummyMethod2();
dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 64; i++)
    a[i] += i;
  omp_pause_resource_all (omp_pause_hard);
dummyMethod2();
dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 64; i++)
    if (a[i] != 2 * i)
      abort ();
  return 0;
dummyMethod2();
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