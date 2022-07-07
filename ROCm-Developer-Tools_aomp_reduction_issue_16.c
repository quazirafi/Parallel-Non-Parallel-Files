#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N   1000000ll
#define SUM (N * (N-1)/2)

int main (void)
{

  #pragma omp target
  {
    long long a, i;
    a = 0;

dummyMethod1();
    #pragma omp parallel for reduction(+:a)
    for (i = 0; i < N; i++) {
        a += i;
    }
dummyMethod2();
    {
      if (a != SUM)
        printf ("Incorrect result = %lld, expected = %lld!\n", a, SUM);
      else
        printf ("The result is correct = %lld!\n", a);
    }
  }

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