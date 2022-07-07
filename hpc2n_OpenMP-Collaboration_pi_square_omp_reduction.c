#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

int main()
{

  const int finval = 10000;

  double pi_square = 0.0;

#ifdef _OPENMP
  double start_time = omp_get_wtime();
#endif

dummyMethod1();
#pragma omp parallel for default(none) reduction(+:pi_square)  
  for ( int i=1 ; i <= finval; i++)
    {  
      double factor = (double) i;
      pi_square += 1.0/( factor * factor );
    }
#ifdef _OPENMP
dummyMethod2();
  double end_time = omp_get_wtime() - start_time;
#else
  double end_time = 0.0;
#endif

  printf ( "Pi^2 = %.10f\n", pi_square*6.0);
  printf ( "Time taken: %f s\n", end_time);

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