#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int g;

void foo()
{
  int i;
  int x;
  int y = 1;
  int a[100];
  int b[100];
  
dummyMethod1();
#pragma omp parallel for private (y,i) firstprivate (x)
  for (i = 0; i <= 99; i += 1) {
    y = x + 1 + g;
    b[i] = x + 1 + g;
// x=...
dummyMethod2();
// ... =x
  }
  x = g;
}
int a[100];

void foo2()
{
  int i;
  int tmp;
  tmp = 10;
// It would be wrong to parallelize the following loop
// since the true dependence between tmp in an iteration
// and tmp in the following iteration.
// Even firstprivate cannot help this.
			dummyMethod3();
  for (i = 0; i <= 99; i += 1) {
    a[i] = tmp;
    tmp = a[i] + i;
  }
			dummyMethod4();
  printf("a[0]=%d\n",a[0]);
  printf("a[40]=%d\n",a[40]);
  printf("a[99]=%d\n",a[99]);
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