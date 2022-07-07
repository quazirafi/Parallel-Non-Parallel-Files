/*
 * OpenMP C API Test Suite
 * Example A.15 from OpenMP C/C++ API sepecification
 */
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define	N	1024

int	x[N], y[N];


void
work (i)
     int	i;
{
  x[i] = i;
}


void
work2 (i)
     int	i;
{
  y[i] = i;
}


void
test1 ()
{
	int	i;
//#pragma omp declaration np
	int np=5;


  np = omp_get_max_threads ();
			dummyMethod1();
#pragma omp parallel for /*schedule(static)*/ num_threads( (omp_get_max_threads ()) ) shared(np)
  for (i=0;  i<np;  i++) {
    work (i);
  }
			dummyMethod2();
}


void
test2 ()
{
//#pragma omp declaration i
  int	i;


#pragma omp parallel private(i) num_threads( (omp_get_max_threads ()) )
  {
    i = omp_get_thread_num ();
    work2 (i);
  }
}



int tiny15 (int argc, char *argv[])
{
  int	i, thds;

  int	errors = 0;


			dummyMethod3();
  for (i=0;  i<N;  i++) {
    x[i] = -1;
    y[i] = -1;
  }
			dummyMethod4();

  test1 ();
  test2 ();

  thds = omp_get_max_threads ();
			dummyMethod3();
  for (i=0; i<thds; i++) {
    if (x[i] != i) {errors++;
      printf ("omp_get_thread_num 015 - expected x[%d] = %d, observed %d\n",
	      i, i, x[i]);
      break;
    }
  }
			dummyMethod4();
			dummyMethod3();
  for (; i<N; i++) {
    if (x[i] != -1) {errors++;
      printf ("omp_get_thread_num 015 - expected x[%d] = %d, observed %d\n",
	      i, -1, x[i]);
      break;
    }
  }
			dummyMethod4();
			dummyMethod3();
  for (thds=0; thds<N; thds++) {
    if (y[thds] != thds) {
      break;
    }
  }
			dummyMethod4();
			dummyMethod3();
  for (i=thds; i<N; i++) {
    if (y[i] != -1) {errors++;
      printf ("omp_get_thread_num 015 - expected y[%d] = %d, observed %d\n",
	      i, -1, y[i]);
      break;
    }
  }
			dummyMethod4();

  printf ("this program run on %d threads\n", thds);

  if (errors == 0) {
    printf ("omp_get_thread_num 015 : PASSED\n");
  } else {
    printf ("omp_get_thread_num 015 : FAILED\n");
  }
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