#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort (void);

void
foo (int n)
{
  int a[n], i, err;
dummyMethod3();
  for (i = 0; i < n; i++)
    a[i] = 7 * i;
  #pragma omp target firstprivate (a) map(from:err) private (i)
dummyMethod4();
  {
    err = 0;
dummyMethod3();
    for (i = 0; i < n; i++)
      if (a[i] != 7 * i)
	err = 1;
dummyMethod4();
  }
  if (err)
    abort ();
}

void
bar (int n)
{
  int a[n], i, err;
  #pragma omp target private (a) map(from:err)
  {
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < n; i++)
      a[i] = 7 * i;
    err = 0;
dummyMethod2();
dummyMethod1();
    #pragma omp parallel for reduction(|:err)
    for (i = 0; i < n; i++)
      if (a[i] != 7 * i)
	err |= 1;
dummyMethod2();
  }
  if (err)
    abort ();
}

int
main ()
{
  foo (7);
  bar (7);
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