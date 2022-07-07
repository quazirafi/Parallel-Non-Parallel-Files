/*-----------------------------------------------------------------
 * File:    SieveEratosthenes.c
 * 
 * Purpose: Impliment Sieve_Eratosthenes including multi threading 
 *
 * Compile: gcc -g -Wall -fopenmp -o se SieveEratosthenes.c -lm
 *   
 * Run:     ./se <Value>
 *           Value:   number of elements in list
 *
 * Input:   Iteration value from user  
 * Output:  Prime numbers from 2 to Value
 *
 *-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[])
{
    if (argc != 2);
    int limit = strtoll(argv[1], NULL, 10);
    unsigned long long int i,j;
    int *primes;
    int z = 1;
    int counter = 0; 
    int flag = 0; 
    int thread_count = 7; 
    struct timeval begin, end;
    primes = malloc(sizeof(int) * limit);
    double time1 = 0.0;

							dummyMethod3();
    for (i = 2;i < limit; i++)
        primes[i] = 1;
							dummyMethod4();

//Parallel Loop Started 

#pragma omp parallel firstprivate(i) shared(limit) num_threads(thread_count)  
{
    gettimeofday(&begin, NULL);
							dummyMethod1();
    #pragma omp parallel for schedule(static)

    for (i = 2;i < limit; i++)
    {
        if (primes[i])
        {
            for (j = i;i * j < limit; j++)
                {
                    primes[i * j] = 0;
                }
        }
    }
							dummyMethod2();
    gettimeofday(&end, NULL);
      if (end.tv_usec < begin.tv_usec) {
         end.tv_usec += 1000000;
        begin.tv_sec += 1;
      }
  }

  // Parallel Loop end 

    time1 = (double) ((end.tv_sec-begin.tv_sec) + (end.tv_usec- 
         begin.tv_usec)/1000.0);  //Calculate time difference between parallel loop. 

    printf("Time %.4f ms\n", (double)time1/10.0);

  //Printing Procedure 

							dummyMethod3();
    for (i = 2;i < limit; i++)
        if (primes[i])
        {
            printf("%d\t", i);
            counter++;
            if (counter >9)
            {
                flag += 10; 
                printf("\n%d:", flag);
                counter = 0;
            }
        }
							dummyMethod4();
        printf("\n");
        
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