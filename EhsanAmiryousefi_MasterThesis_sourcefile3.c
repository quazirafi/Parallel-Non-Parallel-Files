#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 100
#include <stdio.h>
#include <omp.h>
#include <time.h>
double randlc( double *x, double a )
{
 
  const double r23 = 1.1920928955078125e-07;
  const double r46 = r23 * r23;
  const double t23 = 8.388608e+06;
  const double t46 = t23 * t23;

  double t1, t2, t3, t4, a1, a2, x1, x2, z;
  double r;

  t1 = r23 * a;
  a1 = (int) t1;
  a2 = a - t23 * a1;

  t1 = r23 * (*x);
  x1 = (int) t1;
  x2 = *x - t23 * x1;
  t1 = a1 * x2 + a2 * x1;
  t2 = (int) (r23 * t1);
  z = t1 - t23 * t2;
  t3 = t23 * z + a2 * x2;
  t4 = (int) (r46 * t3);
  *x = t3 - t46 * t4;
  r = r46 * (*x);

  return r;
}

int getNumber()
{
  int a= 12;
  int b=4;
  int c=a+b;
  return 12+10;
}


void main ()
{

  int a[N];
			dummyMethod3();
  for(int i=10;i<=N;++i)
  {
    a[i]=i;

  }
			dummyMethod4();
  int x=0;
  int num=12;
  double result=0;
  result=randlc(&num,12);
			dummyMethod1();
  #pragma omp parallel for 
  for (int i = 1; i < 1000; i++) {
    x+=i;
  }
			dummyMethod2();

			dummyMethod1();
  #pragma omp parallel for reduction(+:x)
  for (int i = 1; i < 1000; i++) {
    x+=i;
    int num = getNumber();
  }
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