/* Recurrence, finite differences */

#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  const int N = 10000;		// # of points in domain
  const double h = 0.001;       // distance between points
  double y[N];			// value of fn & later derivative
  const int prune = 1;		// print every...


// load up the function values

dummyMethod1();
#pragma omp parallel for
  for(int i = 0; i < N; i++)
    y[i] = sin(i*h);
  
// print - note cannot use parallel as order counts!
dummyMethod2();

dummyMethod3();
for(int i = 0; i < N; i++)
    {
      if(i%prune == 0)
	printf("%g\t%g\n", i*h, y[i]);
    }

//
dummyMethod4();
// The idea here - start off a bunch of threads. Most of them just deal
// with a contiguous range of values. Thread 0 does point 0 to N_local-1.
// Thread 1 does point N_local to 2*N_local-1. Thread 2 does 2*N_local to
// 3*N_local-1, ... Thread k does points from k*N_local to (k+1)*N_local-1.
// Have each of them compute their values as in the serial case, taking care to 
// save the value needed for the last value in the previous group.

#pragma omp parallel
  {

	// every thread does this

    int N_local;
    double next;

	// N_local is the number of points each thread has to deal with
	// (last thread will pick up the extras)

    N_local = N/omp_get_num_threads();
    
	// now start and stop indices for each thread to work on. The last
	// thread picks up the extras

    int start = omp_get_thread_num()*N_local;
    int stop = start + N_local -1;
    if(omp_get_thread_num() == omp_get_num_threads()-1) {
	stop = stop + N%omp_get_num_threads();
	next = y[N];
    } else {
	next = y[start + N_local];
    }
    
	// ok, all threads meet here.

#pragma omp barrier

	// note - ordinary for, not parallel, but each thread runs their own

							dummyMethod3();
    for(int i = start; i < stop ; i++) {
	y[i] = (y[i+1]-y[i])/h;
    }
							dummyMethod4();

	// next has been saved from the original
    y[stop] = (next - y[stop])/h;

  }  

 	// end of parallel region

  y[N-1] = y[N-2];	// kluge

  printf("\n\n");
   
			dummyMethod3();
  for(int i = 0; i < N; i++)
    {
      if(i%prune == 0)
	printf("%g\t%g\n", i*h, y[i]);
    }
			dummyMethod4();
  

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