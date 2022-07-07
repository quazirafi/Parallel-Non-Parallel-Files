// Based on Author: John Burkardt

/*
* A program that finds the number of prime numbers inside an interval.
* This code was done by me and my fellow friends below for an exercise of
* my parallel computing class on 07/10/2018.
*
* Hiago De Franco Moreira 
* Joao Pedro Doimo Torrezan 
* Tiago Toledo Junior 
* Rosival Rodrigues do Nascimento Neto 
* Felipe Tetzner 
*/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ( int argc, char *argv[] );
void prime_number_sweep ( int n_lo, int n_hi, int n_factor );
int prime_number ( int n );

int main ( int argc, char *argv[] )  {
  int n_lo, n_hi, n_factor;

  n_lo = 5;
  n_hi = 500000;
  n_factor = 10;


  prime_number_sweep ( n_lo, n_hi, n_factor );

  printf ( "  Normal end of execution.\n" );


  return 0;
}// end main

void prime_number_sweep ( int n_lo, int n_hi, int n_factor )
/*  Purpose: PRIME_NUMBER_SWEEP does repeated calls to PRIME_NUMBER.
  Author: John Burkardt
  Parameters:
    Input, int N_LO, the first value of N.
    Input, int N_HI, the last value of N.
    Input, int N_FACTOR, the factor by which to increase N after
    each iteration.
  Example:      N  PRIME_NUMBER
                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579 */
{
  int i, n, primes;
  struct timeval t0, t1;
  long elapsed;


  printf ( "  Call PRIME_NUMBER to count the primes from %d to %d.\n", n_lo, n_hi );
  printf ( "         N        Pi    Time\n" );
  n = n_lo;
  while ( n <= n_hi )   {
    gettimeofday(&t0, 0);

    primes = prime_number ( n );
    gettimeofday(&t1, 0);
    elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;

    printf ( "  %8d  %8d  %.2li\n", n, primes, elapsed); //wtime );

    n = n * n_factor;

  }// end while

  return;
}// end prime_number_sweep

int prime_number ( int n )
/*   PRIME_NUMBER returns the number of primes between 1 and N.
  Author: John Burkardt
  Parameters:
    Input, int N, the maximum number to check.
    Output, int PRIME_NUMBER, the number of prime numbers up to N.  */
{
  int i = 2, j, prime, total = 0;

			dummyMethod1();
  #pragma omp parallel for private(j, prime) reduction(+:total) schedule(dynamic)
  for ( i = 2; i <= n; i++ )  {
    prime = 1;
    for ( j = 2; j < i; j++ )   {
      if ( i % j == 0 )   {
        prime = 0;
        break;
      } //end if
    } // end for
    total = total + prime;
  } // end for
			dummyMethod2();
  return total;
} // end prime_number
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