#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// array types from a parameter list have to be converted to corresponding pointer types
// to avoid segmentation fault.
// Kernel is extracted from cg of npb2.3 omp c benchmarks.
static int colidx[100][100];

static void makea (int colidx[100][100])
{
  int i,j;
dummyMethod1();
#pragma omp parallel for private(i,j)
  for (i = 1; i <= 100; i++) 
   for (j = 1; j <= 100; j++) 
    colidx[i][j] = 0;
}
dummyMethod2();


int main()
{
  makea(colidx);
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