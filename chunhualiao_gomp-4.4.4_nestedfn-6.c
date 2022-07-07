#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort (void);

int j;

int
main (void)
{
  int i;
  //void nested (void) { i = 0; }
dummyMethod1();
#pragma omp parallel for lastprivate (i)
  for (i = 0; i < 50; i += 3)
    ;
  if (i != 51)
dummyMethod2();
    abort ();
dummyMethod1();
#pragma omp parallel for lastprivate (j)
  for (j = -50; j < 70; j += 7)
    ;
  if (j != 76)
dummyMethod2();
    abort ();
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