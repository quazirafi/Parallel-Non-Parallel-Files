#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

void
foo (void)
{
  int i;
  #pragma omp for ordered
dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered
      ;
    }
  #pragma omp for ordered
dummyMethod4();
dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered threads
      ;
    }
  #pragma omp for ordered
dummyMethod4();
dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered threads threads	/* { dg-error "too many .threads. clauses" } */
      ;
    }
  #pragma omp simd
dummyMethod4();
dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered simd
      ;
    }
  #pragma omp simd
dummyMethod4();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered simd simd		/* { dg-error "too many .simd. clauses" } */
      ;
    }
			dummyMethod4();
  #pragma omp for simd ordered
			dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered threads, simd
      ;
    }
			dummyMethod4();
  #pragma omp for simd ordered
			dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered threads, simd, threads, simd	/* { dg-error "too many .threads. clauses" } */
      ;	/* { dg-error "too many .simd. clauses" "" { target *-*-* } .-1 } */
    }
			dummyMethod4();
  #pragma omp for simd ordered(1)	/* { dg-error ".ordered. clause with parameter may not be specified on .#pragma omp for simd. construct" } */
			dummyMethod3();
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered depend(sink: i - 1)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
      #pragma omp ordered depend(source)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
    }
			dummyMethod4();
			dummyMethod1();
  #pragma omp parallel for simd ordered(1)	/* { dg-error ".ordered. clause with parameter may not be specified on .#pragma omp parallel for simd. construct" } */
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered depend(sink: i - 1)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
      #pragma omp ordered depend(source)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
    }
			dummyMethod2();
			dummyMethod1();
  #pragma omp parallel for ordered
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered depend(sink: i - 1)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
      #pragma omp ordered depend(source)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
    }
			dummyMethod2();
			dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 64; i++)
    {
      #pragma omp ordered depend(sink: i - 1)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
      #pragma omp ordered depend(source)	/* { dg-error "clause must be closely nested inside a loop with .ordered. clause with a parameter" } */
    }
			dummyMethod2();
}

void
bar (int x)
{
  switch (x)
    {
    case 0:
      #pragma omp ordered
      ;
      break;
    case 1:
      #pragma omp ordered threads
      ;
      break;
    case 2:
      #pragma omp ordered threads, threads	/* { dg-error "too many .threads. clauses" } */
      ;
      break;
    }
}

void
baz (void)
{
  #pragma omp ordered simd
  ;
  #pragma omp ordered simd, simd		/* { dg-error "too many .simd. clauses" } */
  ;
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