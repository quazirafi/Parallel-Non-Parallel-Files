// Test the handling of two loops under omp for
// watch the loop index replacement (private by default)
// and tje array outlining
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void)
{
  int i, j;
  float** u = (float**) malloc( 500 * sizeof( float*) );
dummyMethod3();
  for( i=0; i<500; i++)
    u[i] = (float*) malloc( 500 * sizeof(float) );

#pragma omp parallel for
dummyMethod4();
dummyMethod1();
  for (i=0; i<500; i++)
    for (j=0; j<500; j++)
    {
      u[i][j] = 0.0;
    }

  return 0;
dummyMethod2();
}
// This code has data races since j is shared
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