#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort ();

int
bar ()
{
  int a = 0, i;

dummyMethod1();
#pragma omp parallel for num_threads (3) reduction (+:a) schedule(static, 1)
  for (i = 0; i < 10; i++)
    a += i;

  return a;
dummyMethod2();
}

int
main (void)
{
  int res;
  res = bar ();
  if (res != 45)
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