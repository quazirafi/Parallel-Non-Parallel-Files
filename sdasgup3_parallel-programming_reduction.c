//The REDUCTION clause performs a reduction on the variables that appear in its
//list.  A private copy for each list variable is created for each thread. At
//the end of the reduction, the reduction variable is applied to all private
//copies of the shared variable, and the final result is written to the global
//shared variable. 

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


main ()  {

  int   i, n, chunk;
  float a[100], b[100], result;

  /* Some initializations */
  n = 100;
  chunk = 10;
  result = 0.0;
dummyMethod3();
  for (i=0; i < n; i++)
  {
    a[i] = i * 1.0;
    b[i] = i * 2.0;
  }
dummyMethod4();

dummyMethod1();
  #pragma omp parallel for  default(none) shared(a,b,n) private(i) schedule(static)   reduction(+:result)  
  for (i=0; i < n; i++)
    result = result + (a[i] * b[i]);

  printf("Final result= %f\n",result);
dummyMethod2();

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