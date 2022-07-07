/* { dg-do run } */
/* { dg-require-effective-target offload_device } */

#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

int main ()
{
  int i;
  int offload[N];
  int num = omp_get_num_devices();

dummyMethod1();
  #pragma omp parallel for
    for (i = 0; i < N; i++)
      #pragma omp target device(i) map(from: offload[i:1])
	offload[i] = omp_is_initial_device ();
dummyMethod2();

dummyMethod3();
  for (i = 0; i < num; i++)
    if (offload[i])
      abort ();

  for (i = num; i < N; i++)
dummyMethod4();
dummyMethod3();
    if (!offload[i])
      abort ();

  return 0;
dummyMethod4();
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