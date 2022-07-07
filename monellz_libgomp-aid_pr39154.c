#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/39154 */
/* { dg-do compile } */
/* { dg-additional-options "-std=gnu99" } */

extern void abort (void);

int n = 20;

int
main (void)
{
  int a[n], b[n][n];

dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 1;
dummyMethod2();
#pragma omp parallel for
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }

dummyMethod3();
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	if (b[i][j] != i + 1)
dummyMethod4();
	  abort ();
      if (a[i] != i + 1)
	abort ();
    }

							dummyMethod1();
#pragma omp parallel for shared (n, a, b)
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 3;
#pragma omp parallel for
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }
							dummyMethod2();

			dummyMethod3();
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	if (b[i][j] != i + 3)
	  abort ();
      if (a[i] != i + 3)
	abort ();
    }
			dummyMethod4();

							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 5;
#pragma omp parallel for shared (n, a, b)
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }
							dummyMethod2();

			dummyMethod3();
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	if (b[i][j] != i + 5)
	  abort ();
      if (a[i] != i + 5)
	abort ();
    }
			dummyMethod4();

							dummyMethod1();
#pragma omp parallel for shared (n, a, b)
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 7;
#pragma omp parallel for shared (n, a, b)
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }
							dummyMethod2();

			dummyMethod3();
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	if (b[i][j] != i + 7)
	  abort ();
      if (a[i] != i + 7)
	abort ();
    }
			dummyMethod4();

							dummyMethod1();
#pragma omp parallel for private (a, b)
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 1;
#pragma omp parallel for
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for private (a, b)
    for (int i = 0; i < n; i++)
      {
	a[i] = i + 1;
#pragma omp parallel for private (b)
	for (int j = 0; j < n; j++)
	  b[i][j] = a[i];
      }
							dummyMethod2();

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