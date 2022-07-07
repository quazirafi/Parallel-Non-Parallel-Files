/* Only the inner loop can be parallelized
 */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void foo()
{
  int n = 100;
  int m = 100;
  double b[n][m];
  int i;
  int j;
  for (i = 0; i <= n - 1; i += 1) {
    
dummyMethod1();
#pragma omp parallel for private (j)
    for (j = 0; j <= m - 1; j += 1) {
      b[i][j] = b[i - 1][j - 1];
    }
dummyMethod2();
  }
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