#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*!!!! include OpenMP header file  here */
#include "omp.h"

/***
 * This example implements a generalized "daxpy" (double a x plus
 * y) operation where a, x, and y are all vectors and
 *
 * result(i) = a(i)*x(i) + y(i)
 */
int main()
{
  double dt, memory_gb;
  int mts, itrial;
  long i, n;
  double *a, *x, *b, *y; 

  struct timeval tstart, tstop;

  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  mts = omp_get_max_threads();
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

    for (itrial=1; itrial<=3; itrial++)
      {
	/* Number of iterations, 10^(itrial+5) */
	n =10* powl(10, itrial+5);

	/***
	 * Arrays for mathematical operations.  Be sure
	 * to free these at the end of the loop!
	 */
	a = (double*)calloc(n, sizeof(double));
	b = (double*)calloc(n, sizeof(double));
	x = (double*)calloc(n, sizeof(double));
	y = (double*)calloc(n, sizeof(double));

	/***
	 * Check that allocation was successful.
	 */
	if ( !(a && b && x && y) )
	  {
	    printf("Error while allocating memory, quitting!\n");
	    exit(1);
	  }
	
	/* Fill in arrays with sample data */
	for (i=0; i<n; i++)
	  {
	    a[i] = sqrt( (double)(i+1) );
	    b[i] = sqrt( (double)(i+2) );
	    x[i] = sqrt( (double)(i+3) );
	  }

	/***
	 * Total memory for 3 arrays of double,
	 * each with size n.
	 */
	memory_gb = 3. * n * sizeof(double) / (double) powl(1024,3);

	/* Start the timer */
	gettimeofday (&tstart, NULL);
	
	/***
	 * Loop over arrays computing y(i) = a(i)*x(i) + b(i)
	 */
/* !!!! Parallelize this loop with OpenMP */
	dummyMethod1();
#pragma omp parallel for
	for (i=0; i<n; i++)
	  y[i] = a[i]*x[i] + b[i];
	dummyMethod2();

	/* Stop the timer and compute the elapsed time. */
	gettimeofday (&tstop, NULL);

	/* Compute the elapsed time */
	dt =
	  (double)(tstop.tv_sec  - tstart.tv_sec) +
	  (double)(tstop.tv_usec - tstart.tv_usec)*1.e-6;

	/***
	 * Print the length of the vectors, memory usage,
	 * and time for the calculation.
	 */
	printf("Length of vectors : %12ld, ", n);
	printf("Total amount of memory : %3.2f GB, ", memory_gb);
	printf("time = %4.3es\n", dt);

	/* Release memory */
	free(a);
	free(b);
	free(x);
	free(y);
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