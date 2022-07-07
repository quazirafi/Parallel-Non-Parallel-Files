#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/56883 */
/* { dg-do compile }
/* { dg-options "-O2 -fopenmp" } */

void
f1 (int ***x)
{
  int i, j, k;
dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < 10; ++i)
    {
    #pragma omp parallel shared(j)
      #pragma omp for
	for (j = 0; j < 10; ++j)
dummyMethod2();
	  {
	  #pragma omp parallel for
	      for (k = 0; k < 10; ++k)
		x[i][j][k] = k;
	  }
    }
}

void
f2 (int ***x)
{
  int i, j, k;
			dummyMethod1();
#pragma omp parallel for schedule(static,1)
  for (i = 0; i < 10; ++i)
    {
    #pragma omp parallel shared(j)
      #pragma omp for schedule(static,1)
	for (j = 0; j < 10; ++j)
	  {
	  #pragma omp parallel for schedule(static,1)
	      for (k = 0; k < 10; ++k)
		x[i][j][k] = k;
	  }
    }
			dummyMethod2();
}

void
f3 (int ***x)
{
  int i, j, k;
			dummyMethod1();
#pragma omp parallel for schedule(runtime)
  for (i = 0; i < 10; ++i)
    {
    #pragma omp parallel shared(j)
      #pragma omp for schedule(runtime)
	for (j = 0; j < 10; ++j)
	  {
	  #pragma omp parallel for schedule(runtime)
	      for (k = 0; k < 10; ++k)
		x[i][j][k] = k;
	  }
    }
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