#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define size 8

#pragma omp declare target
int
identity (int x)
{
  return x;
}

int
expx (int x, int n)
{
dummyMethod3();
  for (int i = 0; i < n - 1; i++)
    x *= x;

  return x;
dummyMethod4();
}

float
init (int x, int y)
{
  int x1 = identity (identity (identity (identity (x))));
  int y1 = identity (identity (identity (identity (y))));

  int x2 = expx (x1, 2);
  int y2 = expx (y1, 2);

  return (x2 + y2);
}
#pragma omp end declare target

int
main ()
{
  int i, j;
  int a[size][size];

#pragma omp target teams map(to:a[:size][:size])
			dummyMethod1();
#pragma omp distribute parallel for default(none) private(i, j) shared(a)
  for (i = 0; i < size; ++i)
    for (j = 0; j < size; ++j)
      a[i][j] = init (i, j);
			dummyMethod2();

			dummyMethod3();
  for (i = 0; i < size; ++i)
    for (j = 0; j < size; ++j)
      if (i * i + j * j != a[i][j])
       __builtin_abort ();
			dummyMethod4();

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