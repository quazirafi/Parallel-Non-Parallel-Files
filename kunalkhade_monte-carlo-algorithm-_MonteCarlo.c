/*-----------------------------------------------------------------
 * File:    SieveEratosthenes.c
 * 
 * Purpose: Impliment Monte Carlo algorithm including multi threading 
 *
 * Compile: gcc -g -Wall -fopenmp -o mc MonteCarlo.c -lm
 *   
 * Run:     ./mc <Value>
 *           Value:   number of elements in list
 *
 * Input:   Iteration value from user  
 * Output:  Value of Pi using Numerical Approach
 *-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <math.h>
#include <sys/time.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SEED 35791246

int main(int argc, char* argv[])
{
	if (argc != 2);
	int niter = strtoll(argv[1], NULL, 10);
    double x,y;                     //x,y value for the random coordinate
    int i;                          //loop counter
    int count=0;                //Count holds all the number of how many good coordinates
    double z;                       //Used to check if x^2+y^2<=1
    double pi;                      //holds approx value of pi
    int numthreads = 8;
    double time1 = 0.0;
    struct timeval begin, end;
    srand(SEED);
    #pragma omp parallel firstprivate(x, y, z, i) shared(count) num_threads(numthreads)
    {
        srandom((int)time(NULL) ^ omp_get_thread_num());    //Give random() a seed value
        
 		gettimeofday(&begin, NULL);
															dummyMethod1();
        #pragma omp parallel for schedule(static)

        for (i=0; i<niter; ++i)              //main loop
        {
            x = (double)random()/RAND_MAX;      //gets a random x coordinate
            y = (double)random()/RAND_MAX;      //gets a random y coordinate
            z = ((x*x)+(y*y));          //Checks to see if number is inside unit circle
            printf("Z: %f\n", z);
        if (z<=1)
        {
                count++;            //if it is, consider it a valid random point
        }
      gettimeofday(&end, NULL);
      if (end.tv_usec < begin.tv_usec) {
         end.tv_usec += 1000000;
        begin.tv_sec += 1;
      }
    }
															dummyMethod2();
        //print the value of each thread/rank
    }
        pi = ((double)count/(double)(niter*numthreads))*4.0;
        printf("Pi: %f\n", pi);
       time1 = (double) ((end.tv_sec-begin.tv_sec) + (end.tv_usec- 
         begin.tv_usec)/1000.0);
          printf("Time %.4f ms\n", (double)time1/10.0);
          printf("Error Value = %.6f \n" , 3.141592 - pi);
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