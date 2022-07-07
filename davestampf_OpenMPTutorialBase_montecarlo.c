/* Monte Carlo simulation of pi*/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

unsigned int seed = 1;  /* random number seed */
const unsigned int rand_max = 32768;

double rannum()
{
#pragma omp threadprivate(seed)
  unsigned int rv;
  seed = seed * 1103515245 + 12345;
  rv = ((unsigned)(seed/65536) % rand_max);
  
  return (double)rv/rand_max;
}

int main()
{
  const int N = 1000000000;      /* number of random numbers   */
  const double r = 1.0;  /* radius of unit circle */

  int i;

  double x, y;   /* function inputs */
  double sum = 0.0;
  double Q = 0.0;

#pragma omp threadprivate(seed)

#pragma omp parallel
  {
    seed = omp_get_thread_num()+1;
  }

			dummyMethod1();
#pragma omp parallel for private(x,y) reduction(+:sum)
  for(i = 0; i < N; i++)
    {
      /* random number, can't use library function, not thread safe */
      x = rannum();      
      y = rannum();
      
      if((x*x + y*y) < r)
	{
	  sum = sum+1.0;
	}
    }
			dummyMethod2();

  Q = 4.0*sum*1.0/N;
  
  printf("%.9g\n", Q);

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