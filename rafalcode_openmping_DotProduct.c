#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAXTHRDS 124

//edited by brett becker, 14/11/2005.  From "Parallel Computing on Heterogeneous Networks" by 
//Dr. Alexey Lastovetsky, Wiley Interscience, 2003, ISBN 0-471-22982-2

double GetTime()
{
  //returns number of seconds on system clock
  // struct timeval time; // can't be done, storage size not known
  struct timeval *time= malloc(sizeof(struct timeval));
  gettimeofday(time, NULL);
  double ret = (double)(time->tv_sec) + (double)(time->tv_usec)/1000000.;
  free(time);
  return ret;
}
int main()
{
  double GetTime();
  double *x, *y, dot_prod, start, end, elapsed;
  int num_of_thrds, vec_len, i, j;
  num_of_thrds = omp_get_num_procs();
  omp_set_num_threads(num_of_thrds);
  
  printf("Number of Threads = %d\n", num_of_thrds);	
  printf("Vector length = ");
  if (scanf("%d", &vec_len)<1) 
    {
      printf("Check input for vector length. Bye.\n");
      return -1;
    }
  
  x = malloc(vec_len*sizeof(double));
  y = malloc(vec_len*sizeof(double));
			dummyMethod3();
  for (i=0; i<vec_len; i++)
    {
      x[i] = rand();
      y[i] = rand();
    }
			dummyMethod4();
  
  dot_prod = 0;
  
  start= GetTime();
			dummyMethod1();
  #pragma omp parallel for reduction(+: dot_prod)
  for (i=0; i<vec_len; i++)
    {
      dot_prod += x[i]*y[i];
    }
			dummyMethod2();
  end = GetTime();
  printf("Dot Product = %g\n", dot_prod);
  printf("elapsed = %f\n", end-start);

  free(x);
  free(y);

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