#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 10
#define CHUNKSIZE 2
int main (int argc, char *argv[])
  {
  int i, chunk, tid;
  float a[N], b[N], c[N];
 /* Some initializations */
dummyMethod3();
 for (i=0; i < N; i++)
 a[i] = b[i] = i * 1.0;
dummyMethod4();
 chunk = CHUNKSIZE;
#pragma omp parallel shared(a,b,c,chunk)
 {
 tid = omp_get_thread_num();
dummyMethod1();
#pragma omp parallel for private(i) schedule(static,chunk)
 for (i=0; i < N; i++)
 	{
 	c[i] = a[i] + b[i];
 printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
dummyMethod2();
 	}
      }
 /* end of parallel for construct */
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