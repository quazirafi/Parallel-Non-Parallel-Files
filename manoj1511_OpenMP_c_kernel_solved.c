#include <stdio.h>
#include <math.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

int main()
{
  double deltax, dt, x, area;
  int mts, itrial;
  long i, n;

  struct timeval tstart, tstop;
  
  /* Get the number of threads using the _OPENMP #define */
#ifdef _OPENMP
  mts = omp_get_max_threads();
  printf("Method 1 :: Number of Threads is %d\n", mts);
#endif

  /***
   * Compute pi using midpoint-rule integration with varying
   * numbers of points.
   */
  for (itrial=1; itrial<=4; itrial++)
    {
      /* Number of iterations, 10^(itrial+5) */
      n = powl(10, itrial+5);

      /* Integration grid spacing */
      deltax = 2. / (double) n;

      /* Start the timer */
      gettimeofday (&tstart, NULL);
      
      /* Compute x values */
/*!!!! Add the OpenMP statement here */ 
/*!!!! What needs to be private? */ 

											dummyMethod1();
#pragma omp parallel for default(none) private(i,x,area) shared(n,deltax)
      for (i=1; i<=n; i++){
	x = -1. + i*deltax;
        area = sqrt(1.-x*x) * deltax;
        if(area<0.0)printf("iter %ld error: %f\n",i,area);
      }
											dummyMethod2();

      /* Stop the timer */
      gettimeofday (&tstop, NULL);

      /* Compute the elapsed time */
      dt =
	(double)(tstop.tv_sec  - tstart.tv_sec) +
	(double)(tstop.tv_usec - tstart.tv_usec)*1.e-6;
	
      /* Print the timing results */
      printf("Number of intervals : %ld, time = %fs\n", n, dt);
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