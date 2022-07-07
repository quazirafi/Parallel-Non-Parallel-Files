#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//Variable examples of using simd directives
void foo (int n, double *a, double* b)
{
#pragma omp simd
dummyMethod3();
  for (int i=0; i<n; i++)
    a[i]=b[i];
}
dummyMethod4();

void foo2 (int n, double *a, double* b)
{
#pragma omp simd safelen(16)
dummyMethod3();
  for (int i=0; i<n; i++)
    a[i]=b[i];
}
dummyMethod4();

void foo3 (int n, double *a, double* b)
{
  int j=0;
#pragma omp simd simdlen(16)
dummyMethod3();
  for (int i=0; i<n; i++,j++)
  {
    a[i]=b[i]+j;
  }
dummyMethod4();
}

void foo32 (int n, double *a, double* b)
{
  int j=0, k=0;
#pragma omp simd linear(j,k)
dummyMethod3();
  for (int i=0; i<n; i++,j++,k++)
  {
    a[i]=b[i]+j+k;
  }
dummyMethod4();
}

void foo33 (int n, double *a, double* b)
{
  int j=0, k=0;
#pragma omp simd linear(j,k:1)
			dummyMethod3();
  for (int i=0; i<n; i++,j++,k++)
  {
    a[i]=b[i]+j+k;
  }
			dummyMethod4();
}

void fooAligned (int n, double *a, double* b)
{
  int j=0, k=0;
#pragma omp simd aligned(j,k)
			dummyMethod3();
  for (int i=0; i<n; i++,j++,k++)
  {
    a[i]=b[i]+j+k;
  }
			dummyMethod4();
}


void fooAligned2 (int n, double *a, double* b)
{
  int j=0, k=0;
#pragma omp simd aligned(j,k:1)
			dummyMethod3();
  for (int i=0; i<n; i++,j++,k++)
  {
    a[i]=b[i]+j+k;
  }
			dummyMethod4();
}

double work( double *a, double *b, int n )
{
   int i; 
   double tmp, sum;
   sum = 0.0;
   #pragma omp simd private(tmp) reduction(+:sum)
					dummyMethod3();
   for (i = 0; i < n; i++) {
      tmp = a[i] + b[i];
      sum += tmp;
   }
					dummyMethod4();
   return sum;
}


#define N 45
int a[N], b[N], c[N];

void foo4(int i, double* P)
{
  int j; 
#pragma omp simd lastprivate(j)
			dummyMethod3();
  for (i = 0; i < 999; ++i) {
    j = P[i];
  }
			dummyMethod4();
}

void work2( double **a, double **b, double **c, int n )
{
  int i, j;
  double tmp;
#pragma omp for simd collapse(2) private(tmp)
			dummyMethod3();
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tmp = a[i][j] + b[i][j];
      c[i][j] = tmp;
    }
  }  
			dummyMethod4();
}

void work3( double **a, double **b, double **c, int n )
{
  int i, j;
  double tmp;
			dummyMethod1();
#pragma omp parallel for simd collapse(2) private(tmp)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tmp = a[i][j] + b[i][j];
      c[i][j] = tmp;
    }
  }  
			dummyMethod2();
}

// declare simd can show up several times!
#pragma omp declare simd simdlen(1) notinbranch
float bar(int * p) {
   *p = *p +10;
   return *p; 
}

// declare simd can show up several times!
#pragma omp declare simd linear(p:1)
#pragma omp declare simd uniform(p)
#pragma omp declare simd simdlen(1) notinbranch
float bar2(int * p) {
   *p = *p +10;
   return *p; 
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