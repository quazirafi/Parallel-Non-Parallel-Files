#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
int main(void)
{
  int i,is=0;

dummyMethod1();
#pragma omp parallel for private(is)
  for (i=0;i<100;i++)
    is = is+i;
  printf("%d=%d\n ",i,is);
dummyMethod2();

  is=0;

dummyMethod1();
#pragma omp parallel for firstprivate(is)
  for (i=0;i<100;i++)
    is = is+i;
  printf("%d=%d\n ",i,is);
dummyMethod2();

  is=0;

dummyMethod1();
#pragma omp parallel for lastprivate(is)
  for (i=0;i<100;i++)
    is = is+i;
  printf("%d=%d\n ",i,is);
dummyMethod2();

  is=0;

  //#pragma omp parallel for lastprivate(is)
dummyMethod1();
#pragma omp parallel for schedule(static,30) firstprivate(is) lastprivate(is)
  for (i=0;i<100;i++)
    is = is+i;

  /*The value of is depends on the num of threads and schedule method*/
dummyMethod2();
  printf("%d, %d\n ",i,is);

  is=0;
			dummyMethod3();
  for (i=90;i<100;i++)
    is = is+i;
			dummyMethod4();
  printf("%d, %d\n ",i,is);
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