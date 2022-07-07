#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
     
int sieveOfEratosthenes(int n)
{
   // Create a boolean array "prime[0..n]" and initialize
   // all entries it as true. A value in prime[i] will
   // finally be false if i is Not a prime, else true.
   int primes = 0; 
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);
     
   memset(prime, true,(n+1)*sizeof(bool));
   
   int i, p;
   
   #pragma omp target map(tofrom:prime[1:n])
dummyMethod1();
   #pragma omp teams distribute parallel for simd schedule (dynamic,100)
   for (p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
		   for(i=p*2; i<=n; i += p)
	           prime[i] = false;
       }
   }
dummyMethod2();
   
   // count prime numbers
   #pragma omp target map(from:prime[1:n]) map(to:primes)
	dummyMethod1();
	#pragma omp teams distribute parallel for reduction(+:primes) schedule(guided)
	for (int p=2; p<=n; p++)
       if (prime[p])
         primes++;
	dummyMethod2();
 
      return(primes);
   }
     
int main()
{
   int n = 100000000;
   double start; 
   double end; 
   start = omp_get_wtime(); 
   printf("%d\n",sieveOfEratosthenes(n));
    end = omp_get_wtime(); 
    printf("Total time: %f seconds\n", end - start);
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