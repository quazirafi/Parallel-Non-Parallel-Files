#include <time.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void)
{

  int i;
  int n=1000000000;
  double sum,a[n];
  double tstart, tend;

dummyMethod1();
  #pragma omp parallel for private(i)
  for (i=0; i<n; i++) a[i]=(i+1)*0.1;

  sum = 0.;
dummyMethod2();
  tstart = omp_get_wtime();

dummyMethod1();
  #pragma omp parallel for default(none) shared(n,a) private(i) reduction(+:sum)
  for (i=0; i<n; i++)  sum += a[i];
  /*-- End of parallel reduction --*/
dummyMethod2();

  tend = omp_get_wtime();
  printf("Value of sum after parallel region: %f\n",sum);
  printf("Elapsed time: %f\n", tend-tstart);

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