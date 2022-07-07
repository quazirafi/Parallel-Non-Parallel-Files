/* { dg-do compile } */

/******************************************************************************
* OpenMP Example - Combined Parallel Loop Work-sharing - C/C++ Version
* FILE: omp_workshare3.c
* DESCRIPTION:
*   This example attempts to show use of the parallel for construct.  However
*   it will generate errors at compile time.  Try to determine what is causing
*   the error.  See omp_workshare4.c for a corrected version.
* SOURCE: Blaise Barney  5/99
* LAST REVISED: 03/03/2002
******************************************************************************/

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N       50
#define CHUNKSIZE   5

main ()  {

int i, chunk, tid;
float a[N], b[N], c[N];

/* Some initializations */
dummyMethod3();
for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;
dummyMethod4();

			dummyMethod1();
#pragma omp parallel for     shared(a,b,c,chunk)  private(i,tid)  schedule(static,chunk)
  for (i=0; i < N; i++)
    {
    c[i] = a[i] + b[i];
    printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
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