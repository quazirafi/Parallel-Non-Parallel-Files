/**
 * @file    sieve.c
 * @author  Brian Reece
 * @date    12/13/2021
 */

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

unsigned long sieve(unsigned long *primes, const unsigned long n)
{
  unsigned long i, j, curr;
  primes[0] = 2;
  curr = 1;

  for (i = 3; i <= n; i++)
  {
    char prime = 1;
dummyMethod1();
    #pragma omp parallel for
    for (j = 0; j < curr; j++)
    {
      if (i % primes[j] == 0)
        prime = 0;
    }
dummyMethod2();

    if (prime == 1)
    {
      printf("%lld, ", i);
      primes[curr++] = i;
    }
  }
  printf("\n");

  return curr;
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