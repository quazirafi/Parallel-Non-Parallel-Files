/******************************************************************************
* OpenMP Example - Combined Parallel Loop Work-sharing - C/C++ Version
* FILE: omp_workshare4.c
* DESCRIPTION:
*   This is a corrected version of the omp_workshare3.c example. Corrections
*   include removing all statements between the parallel for construct and
*   the actual for loop, and introducing logic to preserve the ability to 
*   query a thread's id and print it from inside the for loop.
* SOURCE: Blaise Barney  5/99
* LAST REVISED:
******************************************************************************/

#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N       50
#define CHUNK   5

main ()  {

int i, n, chunk, tid;
float a[N], b[N], c[N];
char first_time;

/* Some initializations */
dummyMethod3();
for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
n = N;
dummyMethod4();
chunk = CHUNK;
first_time = 'y';

			dummyMethod1();
#pragma omp parallel for     \
  shared(a,b,c,n)            \
  private(i,tid)             \
  schedule(static,chunk)     \
  firstprivate(first_time)

  for (i=0; i < n; i++)
    {
    if (first_time == 'y')
      {
      tid = omp_get_thread_num();
      first_time = 'n';
      }
    c[i] = a[i] + b[i];
    printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
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