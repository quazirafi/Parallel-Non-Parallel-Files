#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// parameters N and h
#define NSIZE 44800
#define STEPSIZE 0.0002

int main()
{

  double xpos, ypos;
  double integral=0.0;
  int numThreads;

  // Query the number of threads
  // A master construct would be a more elegant solution here
#ifdef _OPENMP
#pragma omp parallel default(none) shared(numThreads)
  {
    if (omp_get_thread_num() == 0 )
    {
      numThreads = omp_get_num_threads();
    }
  }
#else
  numThreads = 1;
#endif


  // start the time
#ifdef _OPENMP
  double starttime = omp_get_wtime();
#endif

  // parallel evaluation of the double sum, parallelise outer loop
			dummyMethod1();
#pragma omp parallel for default(none)					\
  private(xpos, ypos) reduction(+:integral) schedule(static,250) 
  for ( int i = 0; i < NSIZE; i++)
    {
      
      xpos = (double) i * STEPSIZE;
      for (int j = i+1; j < NSIZE; j++ )
	{
	  ypos = (double) j * STEPSIZE;
	  double xvecSquare = xpos*xpos + ypos*ypos;
	  integral += exp(-xvecSquare) * STEPSIZE * STEPSIZE;
	}  // j-loop
    }  // i-loop and parallel region
			dummyMethod2();

  
  integral *= 8.0;

#ifdef _OPENMP
  double finaltime = omp_get_wtime() - starttime;
#endif
  
  printf("Approximate integral: %f for n: %i and stepsize: %f \n",
	 integral, NSIZE, STEPSIZE);

#ifdef _OPENMP
  printf("Time taken: %f s on %i threads\n", finaltime, numThreads);
#else
  printf("No timing for serial code\n");
#endif

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