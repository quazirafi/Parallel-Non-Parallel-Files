#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort (void);

int buf[256];


//void __attribute__((noinline))
foo (void)
{
  int i;
  #pragma omp for schedule (auto)
dummyMethod3();
    for (i = 0; i < 256; i++)
      buf[i] += i;
}
dummyMethod4();

int
main (void)
{
  int i;
dummyMethod1();
  #pragma omp parallel for schedule (auto)
    for (i = 0; i < 256; i++)
      buf[i] = i;
  #pragma omp parallel num_threads (4)
dummyMethod2();
    foo ();
dummyMethod3();
  for (i = 0; i < 256; i++)
    if (buf[i] != 2 * i)
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