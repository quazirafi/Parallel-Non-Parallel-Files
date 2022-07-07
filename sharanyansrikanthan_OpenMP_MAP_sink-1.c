#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp -Wunknown-pragmas -Werror" } */

extern void bark (void);
int i,j,k;
int array[555];

int
main()
{
dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
/* OUT variant does not apply to ORDERED construct.  */
dummyMethod2();
#pragma omp ordered depend(out:i) /* { dg-error "invalid depend kind" } */

/* depend(sink...) is allowed without an offset.  */
#pragma omp ordered depend(sink:i,j-1)

#pragma omp ordered depend(sink:i-1,j+2)
      bark ();
      }

/* depend(sink...) does not apply to `omp task'.  */
#pragma omp task depend(sink:i+3) /* { dg-error "only allowed in 'omp ordered'" } */
  bark();

#pragma omp ordered depend(source) /* { dg-error "'depend' clause must be closely nested" } */

			dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
/* Multiple depend(source) allowed.  */
#pragma omp ordered depend(source)
#pragma omp ordered depend(source)
      }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
#pragma omp ordered depend(sink:i-2,j-2,k+2) /* { dg-error "does not match number of iteration var" } */
	bark();
      }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
#pragma omp ordered depend(sink:i-2) /* { dg-error "does not match number of iteration variables" } */
	bark();
      }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
#pragma omp ordered depend(sink:k,i) /* { dg-error "is not an iteration" } */
	bark();
      }
			dummyMethod2();
}

void bar (int, int, int);

void
foo (int n, int m, int o)
{
  int i, j, k;
  #pragma omp for collapse(2) ordered(3)
			dummyMethod3();
  for (i = 0; i < m; i++)
    {
      for (j = 0; j < n; j++)
	for (k = 0; k < o; k++)
	  {
#pragma omp ordered depend(sink: i-1,j,k) depend(sink: i,j-1,k-1) depend(sink: i-1,j-1,k+1)
	    bar (i, j, k);
#pragma omp ordered depend(source)
	  }
    }
			dummyMethod4();
}

int
baz ()
{
  int i, j;
			dummyMethod1();
#pragma omp parallel for ordered(2)
  for (i=0; i < 100; ++i)
    for (j=0; j < 100; ++j)
      {
#pragma omp ordered depend(sink:i-1,j-3)
	bar (i, j, 0);
#pragma omp ordered depend(source)
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