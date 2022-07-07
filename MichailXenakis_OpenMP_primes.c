#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define UPTO 10000000

long int count,      /* number of primes */
         lastprime;  /* the last prime found */
		 
float start,
	  end,
	  serial_time,
	  parallel_time;

void serial_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;
	start = omp_get_wtime();
	dummyMethod3();
	for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
		num = 2*i + 3;

		divisor = 1;
		do 
		{
			divisor += 2;                  /* Divide by the next odd */
			quotient  = num / divisor;  
			remainder = num % divisor;  
		} while (remainder && divisor <= quotient);  /* Don't go past sqrt */

		if (remainder || divisor == num) /* num is prime */
		{
			count++;
			lastprime = num;
		}
	}
	dummyMethod4();
	end = omp_get_wtime();
	serial_time = end - start;
}


void openmp_primes(long int n) {
	long int i, num, divisor, quotient, remainder;
	omp_set_num_threads(4);
	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;
	start = omp_get_wtime();
	/* 
	 * Parallelize the serial algorithm but you are NOT allowed to change it!
	 * Don't add/remove/change global variables
	 */
			dummyMethod1();
	#pragma omp parallel for private(num, divisor, quotient, remainder) schedule(dynamic) reduction (+: count) 
		for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
			num = 2*i + 3;
			divisor = 1;
			do 
			{
				divisor += 2;                  /* Divide by the next odd */	
				quotient  = num / divisor;  
				remainder = num % divisor;  
						
			} while (remainder && divisor <= quotient);  /* Don't go past sqrt */

			if (remainder || divisor == num) /* num is prime */
			{
				count++;
				lastprime = num;
			}
		}
			dummyMethod2();
	end = omp_get_wtime();
	parallel_time = end - start;	
}


int main()
{
	printf("Serial and parallel prime number calculations:\n\n");
	
	/* Time the following to compare performance 
	 */
	serial_primes(UPTO);        /* time it */
	printf("[serial] count = %ld, last = %ld (time = %f)\n", count, lastprime, serial_time);
	openmp_primes(UPTO);        /* time it */
	printf("[openmp] count = %ld, last = %ld (time = %f)\n", count, lastprime, parallel_time);
	
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