#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


/* Remark: Make sure arry is larger than L3 */
#define VLENG  500000000


// switch parallel initialisation
#define PARALLEL_INI

// switch for calloc instead of malloc
//#define USE_CALLOC

// switch parallel verification
#define PARALLEL_CHECK

int main()
{

  double *a, *b, *c;

  int num_threads;

  double start_time, init_time, calc_time; 

#ifdef USE_CALLOC
  printf("Using calloc to allocate the memory\n");
  a = calloc(VLENG, sizeof(double));
  b = calloc(VLENG, sizeof(double));
  c = calloc(VLENG, sizeof(double));
#else
  printf("Using malloc to allocate the memory\n");
  a = malloc(VLENG * sizeof(double));
  b = malloc(VLENG * sizeof(double));
  c = malloc(VLENG * sizeof(double));
#endif

#pragma omp parallel default(none) shared(num_threads) 
  {
    #pragma omp master
    {
      num_threads = omp_get_num_threads();
    }
  }


#ifndef PARALLEL_INI
  printf("serial initialisation!\n");

  start_time = omp_get_wtime();

#else
  printf("parallel initialisation!\n");

  start_time = omp_get_wtime();

			dummyMethod1();
#pragma omp parallel for default(none) shared(a,b,c) schedule(static)
#endif
  for (int i=0; i<VLENG; i++)
    {
      a[i] = 2.0 * (double)i;
      b[i] = 3.0 * (double)i;
      c[i] = (double)i;
    }
			dummyMethod2();

  init_time = omp_get_wtime() - start_time;

  start_time = omp_get_wtime();

			dummyMethod1();
#pragma omp parallel for default(none) shared(a, b, c) schedule(static)
  for(int i=0; i<VLENG; i++)
    {
      c[i] = a[i] * b[i];
    }
			dummyMethod2();

  calc_time =  omp_get_wtime() - start_time;

  printf("Time for inititalisation: %.6f s\n", init_time);
  printf("Size: %10d  Threads: %d  Time: %.6f s\n", VLENG, num_threads, calc_time);

  // Verfication

  int pass=1;

#ifndef PARALLEL_CHECK
  printf("Serial correctness check!\n");

  start_time = omp_get_wtime();

#else
  printf("Parallel correctness check!\n");

  start_time = omp_get_wtime();

#pragma omp parallel for default(none) shared(c) reduction( && : pass) schedule(static)
#endif
			dummyMethod3();
  for(int i = 0; i<VLENG; i++)
    {
      double idb = (double)i;
      double compare = (c[i] - 6.0 * idb * idb )/c[i];
      compare = fabs(compare);
      if ( compare > 1.0E-14)
	{
	  pass = 0;
#pragma omp critical (failprint)
	  {
	    printf("Fail: for i=%d we have c[i]: %f\n", i, c[i]);
	  }
	} // endif	
    }
			dummyMethod4();

  double check_time =  omp_get_wtime() - start_time;

  if ( pass ) 
    { printf("Verification: passed!\n");
    }
  else
    { printf("Verification: failed!!!\n");
    }

  printf("Time for verification: %.6f s\n", check_time);
  
  free (a);
  free (b);
  free (c);

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